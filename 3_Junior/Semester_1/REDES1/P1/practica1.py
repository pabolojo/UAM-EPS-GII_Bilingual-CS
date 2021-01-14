'''
    practica1.py
    Muestra el tiempo de llegada de los primeros 50 paquetes a la interfaz especificada
    como argumento y los vuelca a traza nueva con tiempo actual

    Autor: Javier Ramos <javier.ramos@uam.es>
    2020 EPS-UAM
'''

from rc1_pcap import *
import sys
import binascii
import signal
import argparse
from argparse import RawTextHelpFormatter
import time
import logging
import datetime

ETH_FRAME_MAX = 1514
PROMISC = 1
NO_PROMISC = 0
TO_MS = 10
num_paquete = 0
TIME_OFFSET = 30*60
flag = False

def signal_handler(nsignal,frame):
	global flag
	logging.info('Control C pulsado')
	if handle:
		flag = True
		pcap_breakloop(handle)
		

def procesa_paquete(us,header,data):
	global num_paquete, pdumper, args, flag
	if flag is False: 
		logging.info('Nuevo paquete de {} bytes capturado en el timestamp UNIX {}.{}'.format(header.len,header.ts.tv_sec,header.ts.tv_usec))
		num_paquete += 1
	
		#TODO imprimir los N primeros bytes
		cont = 0
		for byte in data:
			print('{:02X} '.format(byte), end = '', flush = True)
			cont += 1
			if cont == args.nbytes:
				break
			
		print()
	
		#Escribir el tráfico al fichero de captura con el offset temporal
		if args.tracefile is False:
			header.ts.tv_sec += TIME_OFFSET # añadimos 30 min
			pcap_dump(pdumper, header, data)
	
if __name__ == "__main__":
	global pdumper,args,handle
	parser = argparse.ArgumentParser(description='Captura tráfico de una interfaz ( o lee de fichero) y muestra la longitud y timestamp de los 50 primeros paquetes',
	formatter_class=RawTextHelpFormatter)
	parser.add_argument('--file', dest='tracefile', default=False,help='Fichero pcap a abrir')
	parser.add_argument('--itf', dest='interface', default=False,help='Interfaz a abrir')
	parser.add_argument('--nbytes', dest='nbytes', type=int, default=14,help='Número de bytes a mostrar por paquete')
	parser.add_argument('--debug', dest='debug', default=False, action='store_true',help='Activar Debug messages')
	args = parser.parse_args()

	if args.debug:
		logging.basicConfig(level = logging.DEBUG, format = '[%(asctime)s %(levelname)s]\t%(message)s')
	else:
		logging.basicConfig(level = logging.INFO, format = '[%(asctime)s %(levelname)s]\t%(message)s')

	if args.tracefile is False and args.interface is False:
		logging.error('No se ha especificado interfaz ni fichero')
		parser.print_help()
		sys.exit(-1)

	signal.signal(signal.SIGINT, signal_handler)

	errbuf = bytearray()
	handle = None
	handle2 = None
	pdumper = None
	
	#TODO abrir la interfaz especificada para captura o la traza
	if args.interface is False:
		handle = pcap_open_offline(args.tracefile, errbuf)
		if handle is None:
			logging.error('Error: {}'.format(errbuf))
			sys.exit(-1)
	else:
		handle = pcap_open_live(args.interface, ETH_FRAME_MAX, NO_PROMISC, TO_MS, errbuf)

		if handle is None:
			logging.error('Error: {}'.format(errbuf))
			sys.exit(-1)
		fname = "captura." + args.interface + "." + datetime.datetime.now().strftime('%Y-%m-%d') + ".pcap"

		handle2 = pcap_open_dead(DLT_EN10MB, ETH_FRAME_MAX)
		if handle2 is None:
			logging.error('Error in pcap_open_dead')
			pcap_close(handle)
			sys.exit(-1)

		pdumper = pcap_dump_open(handle2, fname)
		if pdumper is None:
			logging.error('Error in pcap_dump_open')
			pcap_close(handle)
			pcap_close(handle2)
			sys.exit(-1)
	
	#TODO abrir un dumper para volcar el tráfico (si se ha especificado interfaz) 
	
	
	ret = pcap_loop(handle,-1,procesa_paquete,None)
	if ret == -1:
		logging.error('Error al capturar un paquete')
	elif ret == -2:
		logging.debug('pcap_breakloop() llamado')
	elif ret == 0:
		logging.debug('No mas paquetes o limite superado')
	logging.info('{} paquetes procesados'.format(num_paquete))

	#TODO si se ha creado un dumper cerrarlo
	pcap_close(handle)
		
	if handle2 is not None:
		pcap_close(handle2)

	if pdumper is not None:
		pcap_dump_close(pdumper)
	

