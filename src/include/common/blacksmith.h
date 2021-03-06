/*
 *  blacksmith.h
 *  UDP packet forge
 *
 *  Forjador de pacotes UDP
 */

#ifndef BLACKSMITH_H
  #define BLACKSMITH_H

/**
 *  @brief UDP packet forge
 *
 *  @param ip_dest[in] IP packet destination
 *  @param ip_src[in] IP packet source
 *  @pram dest_port[in] Destination port
 *  @param f_payload[in] This function must return a Packet struct with pkt_pointer containing the pointer to the payload data.
 *  @param p_arg[in] Parameter to f_payload function. If f_payload function is NULL p_arg with be used as payload
 * */
Packet * ForgeUDP(char * ip_dest, char * ip_src, int dest_port, Packet * (*f_payload)(void * arg), void *p_arg);

/**
 *  @brief TCP packet forge
 *
 *  @param ip_dest[in] IP packet destination
 *  @pram dest_port[in] Destination port
 *  @param f_payload[in] This function must return a Packet struct with pkt_pointer containing the pointer to the payload data.
 *  @param p_arg[in] Parameter to f_payload function.
 * */
Packet * ForgeTCP(char * ip_dest, int dest_port, Packet * (*f_payload)(void * arg), void *p_arg);

#endif
