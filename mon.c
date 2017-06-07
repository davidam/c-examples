/***********************************************************************
    mon.c - Un monitor de red simple (sniffer)
    (C) 2002 Josep Damià Carbonell Seguí <josedcs@coitt.es>
    
    Este software se distribuye bajo los términos la licencia GPLv2.

************************************************************************/

/****************************************************************************************
	GLOSARIO:

    - Trama (frame):	unidad de datos que produce el módulo ethernet
    - Paquete IP:		información intercambiada entre el driver ethernet y el módulo IP
    - Segmento TCP:		información intercambiada entre el módulo IP y el módulo TCP
    - Datagrma UDP:     información intercambiada entre el módulo IP y el módulo UDP
****************************************************************************************/

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <netdb.h>

#include <net/if.h>
#include <netinet/if_ether.h>
#include <netinet/ip_icmp.h>
#include <net/if_arp.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/in.h>

/* #include <net/bpf.h> */
#include <netpacket/packet.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>

#define VERSION "v0.3"

#define INTERFACE "eth0"

#define ETHLEN  sizeof(struct ethhdr)
#define IPHLEN  sizeof(struct iphdr)
#define TCPHLEN sizeof(struct tcphdr)

#define BREAK(STR) {perror(STR); exit(-1);}

struct ifreq    ifr;    /*Interface*/
struct ethhdr   *eth;   /*Cabecera ethernet*/
struct iphdr    *ip;    /*Cabecera ip*/
struct arphdr   *arp;   /*Cabecera arp*/
struct icmphdr *icmp;   /*Cabecera icmp*/
struct tcphdr   *tcp;   /*Cabecera tcp*/
struct udphdr   *udp;   /*Cabecera udp*/

int sockfd; /*descriptor de fichero para el socket raw*/

u_char frame[ETHLEN+IPHLEN+TCPHLEN+8192]; /*Buffer para la trama capturada*/

struct sockaddr_ll	sll;    /*Ver "man packet"*/
struct packet_mreq	pmr;

void ayuda(char *bin) {
    printf("Mon - Un monitor de red simple (sniffer)\n");
    printf("(C) 2002 Josep Damià Carbonell Seguí <josedcs@coitt.es>\n");
    printf("uso: %s [-ihV] [-i interficie]\n", bin);
    printf("   -V\tImprime la versión (%s).\n", VERSION);
    printf("   -h\tEsta ayuda.\n");
    printf("   -i\tLa interficie a monitorizar (eth0 por defecto).\n");
    exit(0);
}

void set_ifr_and_sock(char *dev){

    /*Preparamos el socket raw: obtenemos su descriptor*/
    /*Capturemos todos los tipos de tramas posibles: htons(ETH_P_ALL)*/
    if((sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0) BREAK("SOCKET RAW");

    /*Tomamos la interfaz a monitorizar*/
    bcopy(dev, ifr.ifr_name, strlen(dev));

    /*...y obtenemos su índice*/
    if(ioctl(sockfd, SIOCGIFINDEX, &ifr) < 0) BREAK("INDEX INTERFACE");

    /*Debemos ligar el socket con la interfaz*/
    memset((void *)&sll, 0, sizeof(sll));
  	sll.sll_family = AF_PACKET;  /* Siempre es AF_PACKET */
    sll.sll_ifindex = ifr.ifr_ifindex;
  	sll.sll_protocol = htons(ETH_P_ALL);
    if(bind(sockfd, (struct sockaddr *)&sll, sizeof(sll)) < 0) BREAK("BIND");

    /* Evidentemente la ponemos en modo promiscuo*/
    memset((void *)&pmr, 0, sizeof(pmr));
    pmr.mr_ifindex = ifr.ifr_ifindex;
    pmr.mr_type = PACKET_MR_PROMISC;
    if(setsockopt(sockfd, SOL_PACKET, PACKET_ADD_MEMBERSHIP, (void *)&pmr, (socklen_t)sizeof(pmr)) < 0) BREAK("SET SOCKET OPTION");

    /* Ya que estamos sacaremos por pantalla información acerca de esta interfaz*/
    fprintf(stdout, "\n##################################################\n");
    fprintf(stdout, "INTERFICIE -\x1B[7m%s\x1B[0m- EN MODO PROMISCUO\n", dev);

    if (ioctl(sockfd, SIOCGIFADDR, &ifr) < 0) BREAK("GET IP ADDRESS");
    fprintf(stdout, "\tDirección IP:\t\t%s\n", inet_ntoa(((struct sockaddr_in *) &ifr.ifr_addr)->sin_addr));
    if (ioctl(sockfd, SIOCGIFBRDADDR, &ifr) < 0) BREAK("GET BROADCAST ADDRESS");
    fprintf(stdout, "\tDirección Broadcast:\t%s\n", inet_ntoa(((struct sockaddr_in *) &ifr.ifr_broadaddr)->sin_addr));
    if (ioctl(sockfd, SIOCGIFNETMASK, &ifr) < 0) BREAK("GET NETMASK");
    fprintf(stdout, "\tMáscara de Red:\t\t%s\n", inet_ntoa(((struct sockaddr_in *) &ifr.ifr_netmask)->sin_addr));

    if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) < 0) BREAK("GET MAC ADDRESS");
    fprintf(stdout, "\tDirección MAC:\t\t%02X:%02X:%02X:%02X:%02X:%02X\n",  ifr.ifr_hwaddr.sa_data[0], ifr.ifr_hwaddr.sa_data[1],
                                                                            ifr.ifr_hwaddr.sa_data[2], ifr.ifr_hwaddr.sa_data[3],
                                                                            ifr.ifr_hwaddr.sa_data[4], ifr.ifr_hwaddr.sa_data[5]);
    if (ioctl(sockfd, SIOCGIFMTU, &ifr) < 0) BREAK("GET MTU SIZE");
    fprintf(stdout, "\tTamaño de MTU:\t\t%d\n", ifr.ifr_mtu);
    fprintf(stdout, "##################################################\n\n");

}

void sniffing(){

    for(;;){
    	/*Comenzamos a recibir trama*/
     	if (recvfrom(sockfd , frame, sizeof(frame), 0, NULL, NULL) < 0) BREAK("RECVFROM");

      	 /*Detectado nueva trama*/
        fprintf(stdout, "######################################\n");
        fprintf(stdout, "\tREGISTRADA NUEVA TRAMA\n");
        fprintf(stdout, "######################################\n");

        /* ¿Tipo de trama?*/
        eth = (struct ethhdr *)frame;
        switch (ntohs(eth->h_proto)) {
        	case ETH_P_IP:{
         		/*A por el paquete IP*/
           		ip = (struct iphdr *)(frame + ETHLEN);

             	fprintf(stdout, "\nORIGEN: [%02X:%02X:%02X:%02X:%02X:%02X] %s\t->\t",  eth->h_source[0], eth->h_source[1],
                                                                                       eth->h_source[2], eth->h_source[3],
                                                                                       eth->h_source[4], eth->h_source[5],
                                                                                       inet_ntoa(ip->saddr));
         	    fprintf(stdout, "DESTINO: [%02X:%02X:%02X:%02X:%02X:%02X] %s\n",   eth->h_dest[0], eth->h_dest[1],
                                                                                   eth->h_dest[2], eth->h_dest[3],
                                                                                   eth->h_dest[4], eth->h_dest[5],
                                                                                   inet_ntoa(ip->daddr));

                 /*Llamamos a la función paquete_ip()*/
                 paquete_ip();
			} break;
			case ETH_P_ARP || ETH_P_RARP: {
   				/*Petición ARP: Address Resolution Protocol*/
             	arp = (struct arphdr *)(frame + ETHLEN);
              	paquete_arp();/*¿Que tipo es?*/
       		} break;
		}
  		/*Finalmente mostramos por pantalla toda la trama*/
    	dump_frame();

        /*Limpiamos el buffer*/
      	memset(&frame, 0, sizeof(frame));
	}
}

int paquete_ip(){
    /*Mostramos por pantalla los campos de la cabecera del paqute IP recibido*/
    fprintf(stdout, "################################################################");
    fprintf(stdout, "\n\t\tINFORMACIÓN IP (Internet Protocol):\n\n");
    fprintf(stdout, "\tVersión:\t\t\t%d\n", ip->version);
    fprintf(stdout, "\tLongitud de la cabecera:\t%d (%d bits)\n", ip->ihl, ip->ihl * 32);
    fprintf(stdout, "\tTipo de Servicio:\t\t%d\n", ip->tos);
    fprintf(stdout, "\tLongitud Total:\t\t\t%d (%d bits)\n", ntohs(ip->tot_len), ntohs(ip->tot_len) * 8);
    fprintf(stdout, "\tIdentificador:\t\t\t%d\n", ntohs(ip->id));
    fprintf(stdout, "\tDesplazamiento del fragmento:\t%d\n", ip->frag_off);
    fprintf(stdout, "\tTiempo de Vida:\t\t\t%d\n", ip->ttl);
    fprintf(stdout, "\tProtocolo:\t\t\t%d\n", ip->protocol);
    fprintf(stdout, "\tChecksum:\t\t\t%d (%02X)\n", ntohs(ip->check), ntohs(ip->check));
    fprintf(stdout, "\tDirección IP Origen:\t\t%s\n",inet_ntoa(ip->saddr));
    fprintf(stdout, "\tDirección IP Destino:\t\t%s\n",inet_ntoa(ip->daddr));
    fprintf(stdout, "\n#################################################################\n");


    switch(ip->protocol){ /*A por el protocolo*/
        case IPPROTO_TCP:{ /*Es TCP*/
            tcp = (struct tcphdr *)(frame + ETHLEN + IPHLEN);
            segmento_tcp();
        }break;
        case IPPROTO_UDP:{ /*Es UDP*/
            udp = (struct udphdr *)(frame + ETHLEN + IPHLEN);
            datagrama_udp();
        }break;
        case IPPROTO_ICMP:{ /*Datos de control ICMP: Internet Control Message Protocol*/
            icmp = (struct icmphdr *)(frame + ETHLEN + IPHLEN);
            mensaje_icmp();
        }break;
    }
	return(0);
}

int mensaje_icmp(){

    fprintf(stdout, "\n#############################################################################\n");
    fprintf(stdout, "\n\t\tINFORMACIÓN DE ICMP (Internet Control Message Protocol)\n\n");
    fprintf(stdout, "\tTipo de ICMP:");

    switch(icmp->type){
        case ICMP_ECHOREPLY:        fprintf(stdout, "\t\t\tICMP_ECHOREPLY (Echo Reply)\n");  break;
        case ICMP_ECHO:             fprintf(stdout, "\t\t\tICMP_ECHO (Echo Request)\n");       break;
        case ICMP_DEST_UNREACH:     fprintf(stdout, "\t\t\tICMP_DEST_UNREACH (Destination Unreachable)\n"); break;
        case ICMP_SOURCE_QUENCH:    fprintf(stdout, "\t\t\tICMP_SOURCE_QUENCH (Source Quench )\n");    break;
        case ICMP_REDIRECT:         fprintf(stdout, "\t\t\tICMP_REDIRECT (Redirect: change route)\n"); break;
        case ICMP_TIME_EXCEEDED:    fprintf(stdout, "\t\t\tICMP_TIME_EXCEEDED (Time Exceeded)\n");     break;
        case ICMP_PARAMETERPROB:    fprintf(stdout, "\t\t\tICMP_PARAMETERPROB (Parameter Problem)\n"); break;
        case ICMP_TIMESTAMP:        fprintf(stdout, "\t\t\tICMP_TIMESTAMP (Timestamp Request)\n");     break;
        case ICMP_TIMESTAMPREPLY:   fprintf(stdout, "\t\t\tICMP_TIMESTAMPREPLY (Timestamp Reply)\n");  break;
        case ICMP_INFO_REQUEST:     fprintf(stdout, "\t\t\tICMP_INFO_REQUEST (Information Request)\n");break;
        case ICMP_INFO_REPLY:       fprintf(stdout, "\t\t\tICMP_INFO_REPLY (Information Reply)\n");    break;
        case ICMP_ADDRESS:          fprintf(stdout, "\t\t\tICMP_ADDRESS (Address Mask Request)\n");    break;
        case ICMP_ADDRESSREPLY:     fprintf(stdout, "\t\t\tICMP_ADDRESSREPLY (Address Mask Reply)\n"); break;
        default:                    fprintf(stdout, "\t\t\tERROR: %i\n", icmp->type); break;
    }

    if (icmp->type == ICMP_DEST_UNREACH){
    	fprintf(stdout, "\tTipo de ICMP_DEST_UNREACH:");
        switch(icmp->code){
            case ICMP_NET_UNREACH:  fprintf(stdout, "\tICMP_NET_UNREACH (Network Unreachable)\n");  break;
            case ICMP_HOST_UNREACH: fprintf(stdout, "\tICMP_HOST_UNREACH (Host Unreachable)\n");    break;
            case ICMP_PROT_UNREACH: fprintf(stdout, "\tICMP_PROT_UNREACH (Protocol Unreachable)\n");break;
            case ICMP_PORT_UNREACH: fprintf(stdout, "\tICMP_PORT_UNREACH (Port Unreachable)\n");    break;
            case ICMP_FRAG_NEEDED:  fprintf(stdout, "\tICMP_FRAG_NEEDED (Fragmentation Needed/DF set)\n"); break;
            case ICMP_SR_FAILED:    fprintf(stdout, "\tICMP_SR_FAILED (Source Route failed)\n");break;
            case ICMP_NET_UNKNOWN:  fprintf(stdout, "\tICMP_NET_UNKNOWN (Net Unknown)\n");      break;
            case ICMP_HOST_UNKNOWN: fprintf(stdout, "\tICMP_HOST_UNKNOWN (Host Unknown)\n");    break;
            case ICMP_HOST_ISOLATED:fprintf(stdout, "\tICMP_HOST_ISOLATED\n"); break;
            case ICMP_NET_ANO:		fprintf(stdout, "\tICMP_NET_ANO\n"); break;
            case ICMP_HOST_ANO: 	fprintf(stdout, "\tICMP_HOST_ANO\n");  break;
            case ICMP_NET_UNR_TOS: 	fprintf(stdout, "\tICMP_NET_UNR_TOS\n"); break;
            case ICMP_HOST_UNR_TOS: fprintf(stdout, "\tICMP_HOST_UNR_TOS\n");  break;
            case ICMP_PKT_FILTERED: fprintf(stdout, "\tICMP_PKT_FILTERED (Packet filtered)\n"); break;
            case ICMP_PREC_VIOLATION:	fprintf(stdout, "\tICMP_PREC_VIOLATION (Precedence violation)\n"); break;
            case ICMP_PREC_CUTOFF: 	fprintf(stdout, "\tICMP_PREC_CUTOFF (Precedence cut off)\n"); break;
            default: fprintf(stdout, "\tDesconocido\n");
  		}
 	}
    if (icmp->type == ICMP_REDIRECT){
    	fprintf(stdout, "\tTipo de ICMP_REDIRECT:");
        switch(icmp->code){
          case ICMP_REDIR_NET:		fprintf(stdout, "\tICMP_REDIR_NET (Redirect Net)\n");	break;
          case ICMP_REDIR_HOST:		fprintf(stdout, "\tICMP_REDIR_HOST (Redirect Host)\n");	break;
          case ICMP_REDIR_NETTOS:	fprintf(stdout, "\tICMP_REDIR_NETTOS (Redirect Net for TOS\n");	break;
          case ICMP_REDIR_HOSTTOS:	fprintf(stdout, "\tICMP_REDIR_HOSTTOS (Redirect Host for TOS\n"); break;
          default: fprintf(stdout, "\tDesconocido\n");
        }
    }
    if (icmp->type == ICMP_TIME_EXCEEDED){
    	fprintf(stdout, "\tTipo de ICMP_TIME_EXCEEDED:");
        switch(icmp->code){
          case ICMP_EXC_TTL:		fprintf(stdout, "\tICMP_EXC_TTL (TTL count exceeded)\n"); break;
          case ICMP_EXC_FRAGTIME:	fprintf(stdout, "\tICMP_EXC_FRAGTIME (Fragment Reass time exceeded)\n"); break;
          default: fprintf(stdout, "\tDesconocido\n");
        }
    }
    fprintf(stdout, "\tChecksum:\t\t\t%d (%02X)\n", ntohs(icmp->checksum), ntohs(icmp->checksum));
    fprintf(stdout, "\tDirección IP Encaminador:\t%s\n",inet_ntoa(icmp->un.gateway));
    fprintf(stdout, "#############################################################################\n\n");
}

int paquete_arp(){

    fprintf(stdout, "\n#####################################################\n");
    fprintf(stdout, "\t\tINFORMACIÓN ARP:\n");

    switch(ntohs(arp->ar_op)) {
        case ARPOP_REQUEST :
            fprintf(stdout, "\tARP Request\n");
            break;
        case ARPOP_REPLY :
            fprintf(stdout, "\tARP Reply\n");
            break;
        case ARPOP_RREQUEST:
            fprintf(stdout, "\tRARP Request\n");
            break;
        case ARPOP_RREPLY:
            fprintf(stdout, "\tRARP Reply\n");
            break;
        case ARPOP_InREQUEST:
            fprintf(stdout, "\tInARP Request\n");
            break;
        case ARPOP_InREPLY:
            fprintf(stdout, "\tInARP Reply\n");
            break;
        case ARPOP_NAK:
            fprintf(stdout, "\t(ATM)ARP NAK\n");
            break;
        default :
            fprintf(stdout, "\tDesconocido\n");
        break;
    }
    fprintf(stdout, "#######################################################\n\n");
}

int segmento_tcp(){
        fprintf(stdout, "\n#############################################################################\n");
        fprintf(stdout, "\t\tINFORMAIÓN DE TCP (Transmission Control Protocol)\n\n");
        fprintf(stdout, "\tPuerto de Protocolo Origen:\t%i\n", ntohs(tcp->source));
        fprintf(stdout, "\tPuerto de Protocolo Destino:\t%i\n", ntohs(tcp->dest));
		fprintf(stdout, "\tNúmero de secuencia:\t\t%i\n", ntohl(tcp->seq));
        fprintf(stdout, "\tNúmero de secuencia ACK:\t%i\n", ntohl(tcp->ack_seq));
        fprintf(stdout, "\tTamaño de la cabecera:\t\t%d (%d bits)\n", tcp->doff, tcp->doff * 32);
        fprintf(stdout, "\tFlag URG:\t\t\t%d\n", tcp->urg);
        fprintf(stdout, "\tFlag ACK:\t\t\t%d\n", tcp->ack);
        fprintf(stdout, "\tFlag PSH:\t\t\t%d\n", tcp->psh);
        fprintf(stdout, "\tFlag RST:\t\t\t%d\n", tcp->rst);
        fprintf(stdout, "\tFlag SYN:\t\t\t%d\n", tcp->syn);
        fprintf(stdout, "\tFlag FIN:\t\t\t%d\n", tcp->fin);
        fprintf(stdout, "\tTamaño de la ventana:\t\t%d\n", ntohs(tcp->window));
        fprintf(stdout, "\tPuntero Urgente:\t\t%d\n", tcp->urg_ptr);
        fprintf(stdout, "\tChecksum:\t\t\t%d (%02X)\n", ntohs(tcp->check), ntohs(tcp->check));
        fprintf(stdout, "\n#############################################################################\n");
        return(0);
}

int datagrama_udp(){
        fprintf(stdout, "\n#########################################################################\n\n");
        fprintf(stdout, "\t\tINFORMATION OF UDP PROTOCOL\n");
        fprintf(stdout, "\tSource Port Protocol:\t\t%i\n", ntohs(udp->source));
        fprintf(stdout, "\tDestination Port Protocol:\t%i\n", ntohs(udp->dest));
        fprintf(stdout, "\tTamaño del segmento TCP:\t%d (%d bits)\n", ntohs(udp->len), ntohs(udp->len * 8));
        fprintf(stdout, "\tChecksum:\t\t\t%d (%02X)\n", ntohs(udp->check), ntohs(udp->check));
        fprintf(stdout, "#########################################################################\n\n");
        return(0);
}

int dump_frame(){

    int offset = 0;
    int size, lines, mod, i, j;
    unsigned char *p;
    char buffer[17];

    size = ETHLEN + ntohs(ip->tot_len);
    p = (unsigned char *)frame;

    lines = size / 16;
    mod = size % 16;
    buffer[16] = 0;
    
    fprintf(stdout, "###################################################################################\n");
    fprintf(stdout, "\t\tVOLCADO DE LA TRAMA:\n\n");
    for (i = 0; i < lines; i++){
        fprintf(stdout, "\t%04x  ", offset);
        for(j = 0; j < 16; j++){
            fprintf(stdout, "%02X ", *(p+j) & 0xff);
            if((*(p+j) > 32) && (*(p+j) < 127)){
                buffer[j] = *(p+j);
            }
            else {
                buffer[j] = '.';
            }
        }
        fprintf(stdout, "\t%s\n", buffer);
        offset += 16;
        p += 16;
    }

    fprintf(stdout, "\t%04X  ", offset);
    for (i = 0; i < mod; i++){
        fprintf(stdout, "%02X ", *(p+i) & 0xff);
        if((*(p+i) > 32) && (*(p+i) < 127)){
            buffer[i] = *(p+i);
        }
        else {
            buffer[i] = '.';
        }
    }
        for(i = 0; i < (16 - mod); i++) fprintf(stdout, "%02X ", 0x00);

    buffer[mod] = 0;
    fprintf(stdout, "\t%s\n", buffer);
    fprintf(stdout, "###################################################################################\n");
}

void cleanup(){
    close(sockfd);
    exit(0);
}


int main(int argc, char **argv){

    char opt;
    char *interface = INTERFACE;

    while ((opt=getopt(argc, argv,"hVi:"))!=-1) {
      switch(opt) {
         case 'i':
            interface = optarg;
            break;
         case 'V':
           	printf("Versión %s.\n", VERSION);
            exit(0);
         case 'h':
            ayuda(argv[0]);
            break;
         default :
            ayuda(argv[0]);
            exit(0);
      }
    }

    if (getuid() != 0){
        puts("Debes ejecutar Mon como ROOT");
        exit(0);
    }
    set_ifr_and_sock(interface);
    
    signal(SIGHUP, SIG_IGN);
    signal(SIGINT,  cleanup);
    signal(SIGTERM, cleanup);
    signal(SIGKILL, cleanup);
    signal(SIGQUIT, cleanup);

    sniffing();
}

