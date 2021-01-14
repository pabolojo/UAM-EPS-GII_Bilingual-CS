#!/usr/bin/python
'''
    practica3.py
    Programa principal que realiza el análisis de tráfico sobre una traza PCAP.
    Autor: Javier Ramos <javier.ramos@uam.es>
    2020 EPS-UAM
'''


import sys
import argparse
from argparse import RawTextHelpFormatter
import time
import logging
import shlex
import subprocess
import pandas as pd
from io import StringIO
import os
import warnings
warnings.filterwarnings("ignore")
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
import math

'''
    Función: calcularECDF
    Entrada: 
        -datos: lista con los datos sobre los que calcular la ECDF
    Salida: :
        -datos: lista con los valores x (datos de entrada)
        -y: lista con los valores de probabilidad acumulada para cada dato de entrada
    Descripción:  Esta función recibe una lista de datos y calcula la función empírica de distribución 
    acumulada sobre los mismos. Los datos se devuelven listos para ser pintados.
'''
def calcularECDF(datos):
    datos.sort()
    n = len (datos)
    y = [(i-1)/n for i in range(1,n+1)]

    return datos,y



'''
    Función: ejecutarComandoObtenerSalida
    Entrada: 
        -comando: cadena de caracteres con el comando a ejecutar
    Salida: 
        -salida_retorno: cadena de caracteres con el retorno del comando. Este retorno
        es el mismo que obtendríamos por stdout al ejecutar un comando de terminal.

    Descripción: Esta función recibe una cadena con un comando a ejecutar, lo ejecuta y retorna
    tanto el código de resultado de la ejecución como la salida que el comando produzca por stdout
'''
def ejecutarComandoObtenerSalida(comando):
    return subprocess.getoutput(comando)


'''
    Función: pintarECDF
    Entrada:
        -datos: lista con los datos que se usarán para calcular y pintar la ECDF
        -nombre_fichero: cadena de caracteres con el nombre del fichero donde se guardará la imagen
        (por ejemplo figura.png)
        -titulo: cadena de caracteres con el título a pintar en la gráfica
        -titulo_x: cadena de caracteres con la etiqueta a usar para el eje X de la gráfica
        -titulo_y: cadena de caracteres con la etiqueta a usar para el eje Y de la gráfica
    Salida: 
        -Nada

    Descripción: Esta función pinta una gráfica ECDF para unos datos de entrada y la guarda en una imagen
'''
def pintarECDF(datos,nombre_fichero,titulo,titulo_x,titulo_y):
    
    x, y = calcularECDF(datos)
    fig1, ax1 = plt.subplots()
    plt.plot(x, y, '-')
    _ = plt.xticks(rotation=45)
    plt.title(titulo)
    fig1.set_size_inches(12, 10)
    plt.tight_layout()
    plt.locator_params(nbins=20)
    ax1.set_xlabel(titulo_x)
    ax1.set_ylabel(titulo_y)
    plt.savefig(nombre_fichero, bbox_inches='tight')


'''
    Función: pintarSerieTemporal
    Entrada:
        -x: lista de tiempos en formato epoch y granularidad segundos
        -y: lista con los valores a graficar
        -nombre_fichero: cadena de caracteres con el nombre del fichero donde se guardará la imagen
        (por ejemplo figura.png)
        -titulo: cadena de caracteres con el título a pintar en la gráfica
        -titulo_x: cadena de caracteres con la etiqueta a usar para el eje X de la gráfica
        -titulo_y: cadena de caracteres con la etiqueta a usar para el eje Y de la gráfica
    Salida: 
        -Nada

    Descripción: Esta función pinta una serie temporal dados unos datos x e y de entrada y la guarda en una imagen
'''
def pintarSerieTemporal(x,y,nombre_fichero,titulo,titulo_x,titulo_y):
   
    fig1, ax1 = plt.subplots()
    plt.plot(x, y, '-')
    _ = plt.xticks(rotation=45)
    plt.title(titulo)
    fig1.set_size_inches(12, 10)
    plt.gcf().autofmt_xdate()
    plt.gca().xaxis.set_major_locator(mtick.FixedLocator(x))
    plt.gca().xaxis.set_major_formatter(mtick.FuncFormatter(lambda pos,_: time.strftime("%d-%m-%Y %H:%M:%S",time.localtime(pos))))
    plt.tight_layout()
    plt.locator_params(nbins=20)
    ax1.set_xlabel(titulo_x)
    ax1.set_ylabel(titulo_y)
    plt.savefig(nombre_fichero, bbox_inches='tight')


'''
    Función: pintarTarta
    Entrada:
        -etiquetas: lista con cadenas de caracteres que contienen las etiquetas a usar en el gráfico de tarta
        -valores: lista con los valores a graficar
        -nombre_fichero: cadena de caracteres con el nombre del fichero donde se guardará la imagen
        (por ejemplo figura.png)
        -titulo: cadena de caracteres con el título a pintar en la gráfica
        
    Salida: 
        -Nada

    Descripción: Esta función pinta un gráfico de tarta dadas unas etiquetas y valores de entrada y lo guarda en una imagen
'''
def pintarTarta(etiquetas,valores,nombre_fichero,titulo):

   
   
    explode = tuple([0.05]*(len(etiquetas)))
 
    fig1, ax1 = plt.subplots()
    plt.pie(valores, autopct='%1.1f%%', startangle=90, pctdistance=0.85)
    plt.legend(etiquetas, loc="best")
    plt.title(titulo)
    centre_circle = plt.Circle((0,0),0.70,fc='white')
    fig1 = plt.gcf()
    fig1.gca().add_artist(centre_circle)
    fig1.set_size_inches(12, 10)
    ax1.axis('equal')  
    plt.tight_layout()
    plt.savefig(nombre_fichero, bbox_inches='tight')


def salidaParser(salida):
        etiquetas = []
        datos = []

        for linea in salida.split('\n'):
            if linea != '':
                paquete = linea.split('\t')
                etiquetas.append(paquete[1])
                datos.append(int(paquete[0]))

        return etiquetas, datos

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Programa principal que realiza el análisis de tráfico sobre una traza PCAP',
    formatter_class=RawTextHelpFormatter)
    parser.add_argument('--trace', dest='tracefile', default=False,help='Fichero de traza a usar',required=True)
    parser.add_argument('--mac', dest='mac', default=False,help='MAC usada para filtrar',required=True)
    parser.add_argument('--ip_flujo_tcp', dest='ip_flujo_tcp', default=False,help='IP para filtrar por el flujo TCP',required=True)
    parser.add_argument('--port_flujo_udp', dest='port_flujo_udp', default=False,help='Puerto para filtrar por el flujo UDP',required=True)
    parser.add_argument('--debug', dest='debug', default=False, action='store_true',help='Activar Debug messages')
    args = parser.parse_args()

    if args.debug:
        logging.basicConfig(level = logging.DEBUG, format = '[%(asctime)s %(levelname)s]\t%(message)s')
    else:
        logging.basicConfig(level = logging.INFO, format = '[%(asctime)s %(levelname)s]\t%(message)s')

    #Comprobamos que la trama proporcionada existe
    try:
        f = open(args.tracefile)
    except IOError:
        logging.error("No existe la traza proporcionada")
        exit(-1)
    
    f.close()

    #Creamos un directorio a donde volcaremos los resultado e imágenes

    if not os.path.isdir('resultados'):
        os.mkdir('resultados')
  
    #Ejemplo de ejecución de comando tshark y parseo de salida. Se parte toda la salida en líneas usando el separador \n
    logging.info('Ejecutando tshark para obtener el número de paquetes')
    salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e frame.number'.format(args.tracefile))
    nlineas = 0
    for linea in salida.split('\n'):
        if linea != '':
            nlineas +=1

    print('{} paquetes en la traza {}'.format(nlineas,args.tracefile))
    
    #Analisis de protocolos
    
    # Obtener el porcentaje de tráfico IPv4 y NO-IPv4
    # Obtener el porcentaje de tráfico TPC,UDP y OTROS sobre el tráfico IP

    logging.info('Ejecutando tshark para obtener el número de paquetes')
    salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e eth.type -e ip.proto -Y \'eth.type eq 0x0800\''.format(args.tracefile))

    num_ip = 0
    num_tcp = 0
    num_udp = 0
    num_otros = 0
    
    for linea in salida.split('\n'):
        if linea != '':
            paquete = linea.split('\t')
            num_ip += 1
            if paquete[1] == '6':
                num_tcp += 1
            elif paquete[1] == '17':
                num_udp += 1
            else:
                num_otros += 1

    num_noip = nlineas - num_ip
    
    print('{}% paquetes IP, {}% paquetes noIP , {}% paquetes TCP, {}% paquetes UDP, {}% otros paquetes en la traza {}'.format(num_ip*100/nlineas, num_noip*100/nlineas, num_tcp*100/num_ip, num_udp*100/num_ip, num_otros*100/num_ip, args.tracefile))
   
    #Obtención de top 5 direcciones IP
    #Añadir código para obtener los datos y generar la gráfica de top IP origen por bytes
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de top IP origen por bytes')
    command = 'tshark -r %s -T fields -e ip.src -e frame.len -Y \'ip\' | awk \'{ips[$1] = ips[$1] + $2} END {for (ip in ips) {print ips[ip]"\t"ip}}\' | sort -n -k 1 | tail -5' % (args.tracefile)
    salida = ejecutarComandoObtenerSalida(command)
    etiquetas, datos = salidaParser(salida)

    pintarTarta(etiquetas, datos, "resultados/top_ips_orig_bytes.png","Top 5 IPs origen por bytes")

    #Añadir código para obtener los datos y generar la gráfica de top IP origen por paquetes
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de top IP origen por paquetes')
    command = 'tshark -r %s -T fields -e ip.src -Y \'ip\' | awk \'{ips[$1] = ips[$1] + 1} END {for (ip in ips) {print ips[ip]"\t"ip}}\' | sort -n -k 1 | tail -5' % (args.tracefile)
    salida = ejecutarComandoObtenerSalida(command)
    etiquetas, datos = salidaParser(salida)
    
    pintarTarta(etiquetas, datos, "resultados/top_ips_orig_paquetes.png","Top 5 IPs origen por paquetes")

    #Añadir código para obtener los datos y generar la gráfica de top IP destino por paquetes
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de top IP destino por paquetes')
    command = 'tshark -r %s -T fields -e ip.dst -Y \'ip\' | awk \'{ips[$1] = ips[$1] + 1} END {for (ip in ips) {print ips[ip]"\t"ip}}\' | sort -n -k 1 | tail -5' % (args.tracefile)
    salida = ejecutarComandoObtenerSalida(command)
    etiquetas, datos = salidaParser(salida)

    pintarTarta(etiquetas, datos, "resultados/top_ips_dst_paquetes.png","Top 5 IPs destino por paquetes")
        
    #Añadir código para obtener los datos y generar la gráfica de top IP destino por bytes
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de top IP destino por bytes')
    command = 'tshark -r %s -T fields -e ip.dst -e frame.len -Y \'ip\' | awk \'{ips[$1] = ips[$1] + $2} END {for (ip in ips) {print ips[ip]"\t"ip}}\' | sort -n -k 1 | tail -5' % (args.tracefile)
    salida = ejecutarComandoObtenerSalida(command)
    etiquetas, datos = salidaParser(salida)

    pintarTarta(etiquetas, datos, "resultados/top_ips_dst_bytes.png","Top 5 IPs destino por bytes")
        
    #Obtención de top 5 puertos TCP
    #Añadir código para obtener los datos y generar la gráfica de top puerto origen TCP por bytes
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de top puerto origen TCP por bytes')
    command = 'tshark -r %s -T fields -e tcp.srcport -e frame.len -Y \'tcp\' | awk \'{ips[$1] = ips[$1] + $2} END {for (ip in ips) {print ips[ip]"\t"ip}}\' | sort -n -k 1 | tail -5' % (args.tracefile)
    salida = ejecutarComandoObtenerSalida(command)
    etiquetas, datos = salidaParser(salida)

    pintarTarta(etiquetas, datos, "resultados/top_tcp_orig_bytes.png","Top 5 puertos TCP origen por bytes")

    #Añadir código para obtener los datos y generar la gráfica de top puerto destino TCP por bytes
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de top puerto destino TCP por bytes')
    command = 'tshark -r %s -T fields -e tcp.dstport -e frame.len -Y \'tcp\' | awk \'{ips[$1] = ips[$1] + $2} END {for (ip in ips) {print ips[ip]"\t"ip}}\' | sort -n -k 1 | tail -5' % (args.tracefile)
    salida = ejecutarComandoObtenerSalida(command)
    etiquetas, datos = salidaParser(salida)
    
    pintarTarta(etiquetas, datos, "resultados/top_tcp_dst_bytes.png","Top 5 puertos TCP destino por bytes")
        
    #Añadir código para obtener los datos y generar la gráfica de top puerto origen TCP por paquetes
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de top puerto origen TCP por paquetes')
    command = 'tshark -r %s -T fields -e tcp.srcport -Y \'tcp\' | awk \'{ips[$1] = ips[$1] + 1} END {for (ip in ips) {print ips[ip]"\t"ip}}\' | sort -n -k 1 | tail -5' % (args.tracefile)
    salida = ejecutarComandoObtenerSalida(command)
    etiquetas, datos = salidaParser(salida)

    pintarTarta(etiquetas, datos, "resultados/top_tcp_orig_paquetes.png","Top 5 puertos TCP origen por paquetes")
 
    #Añadir código para obtener los datos y generar la gráfica de top puerto destino  TCP por paquetes
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de top puerto destino  TCP por paquetes')
    command = 'tshark -r %s -T fields -e tcp.dstport -Y \'tcp\' | awk \'{ips[$1] = ips[$1] + 1} END {for (ip in ips) {print ips[ip]"\t"ip}}\' | sort -n -k 1 | tail -5' % (args.tracefile)
    salida = ejecutarComandoObtenerSalida(command)
    etiquetas, datos = salidaParser(salida)

    pintarTarta(etiquetas, datos, "resultados/top_tcp_dst_paquetes.png","Top 5 puertos TCP destino por paquetes")

    #Obtención de top 5 puertos UDP
    #Añadir código para obtener los datos y generar la gráfica de top puerto origen UDP por bytes
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de top puerto origen UDP por bytes')
    command = 'tshark -r %s -T fields -e udp.srcport -e frame.len -Y \'udp\' | awk \'{ips[$1] = ips[$1] + $2} END {for (ip in ips) {print ips[ip]"\t"ip}}\' | sort -n -k 1 | tail -5' % (args.tracefile)
    salida = ejecutarComandoObtenerSalida(command)
    etiquetas, datos = salidaParser(salida)

    pintarTarta(etiquetas, datos,  "resultados/top_udp_orig_bytes.png","Top 5 puertos UDP origen por bytes")

    #Añadir código para obtener los datos y generar la gráfica de top puerto destino UDP por bytes
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de top puerto destino UDP por bytes')
    command = 'tshark -r %s -T fields -e udp.dstport -e frame.len -Y \'udp\' | awk \'{ips[$1] = ips[$1] + $2} END {for (ip in ips) {print ips[ip]"\t"ip}}\' | sort -n -k 1 | tail -5' % (args.tracefile)
    salida = ejecutarComandoObtenerSalida(command)
    etiquetas, datos = salidaParser(salida)
    
    pintarTarta(etiquetas, datos,  "resultados/top_udp_dst_bytes.png","Top 5 puertos UDP destino por bytes")

        
    #Añadir código para obtener los datos y generar la gráfica de top puerto origen UDP por paquetes
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de top puerto origen UDP por paquetes')
    command = 'tshark -r %s -T fields -e udp.srcport -Y \'udp\' | awk \'{ips[$1] = ips[$1] + 1} END {for (ip in ips) {print ips[ip]"\t"ip}}\' | sort -n -k 1 | tail -5' % (args.tracefile)
    salida = ejecutarComandoObtenerSalida(command)
    etiquetas, datos = salidaParser(salida)

    pintarTarta(etiquetas, datos, "resultados/top_udp_orig_paquetes.png","Top 5 puertos UDP origen por paquetes")

    
    #Añadir código para obtener los datos y generar la gráfica de top puerto destino UDP por paquetes
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de top puerto destino UDP por paquetes')
    command = 'tshark -r %s -T fields -e udp.dstport -Y \'udp\' | awk \'{ips[$1] = ips[$1] + 1} END {for (ip in ips) {print ips[ip]"\t"ip}}\' | sort -n -k 1 | tail -5' % (args.tracefile)
    salida = ejecutarComandoObtenerSalida(command)
    etiquetas, datos = salidaParser(salida)

    pintarTarta(etiquetas, datos, "resultados/top_udp_dst_paquetes.png","Top 5 puertos UDP destino por paquetes")


    #Obtención de las ECDF de tamaño de los paquetes
    #Añadir código para obtener los datos y generar la gráfica de la ECDF de los tamaños de los paquetes a nivel 2
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de la ECDF de los tamaños de los paquetes a nivel 2')
    #Sentido origen
    command = 'tshark -r %s -T fields -e frame.len -Y \'eth.src eq %s\'' % (args.tracefile, args.mac)
    salida = ejecutarComandoObtenerSalida(command)

    paquetesBytes = []
    
    for linea in salida.split('\n'):
        if linea != '':
            paquetesBytes.append(int(linea))

    pintarECDF(paquetesBytes,"resultados/ecdf_paquetes_bytes_origen.png","Tamaño de los parquetes a nivel 2 (origen)","Bytes/paquete","Porcentaje acumulado de bytes/paquete")
    
    #Sentido destino
    command = 'tshark -r %s -T fields -e frame.len -Y \'eth.dst eq %s\'' % (args.tracefile, args.mac)
    salida = ejecutarComandoObtenerSalida(command)

    paquetesBytes = []
    
    for linea in salida.split('\n'):
        if linea != '':
            paquetesBytes.append(int(linea))

    pintarECDF(paquetesBytes,"resultados/ecdf_paquetes_bytes_destino.png","Tamaño de los parquetes a nivel 2 (destino)","Bytes/paquete","Porcentaje acumulado de bytes/paquete")
    
    #Obtención de series temporales de ancho de banda
    #Añadir código para obtener los datos y generar la gráfica de la serie temporal de ancho de banda con MAC como origen
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de la serie temporal de ancho de banda con MAC como origen')
    salida = ejecutarComandoObtenerSalida('tshark -r %s -qz io,stat,1,,eth.src==%s | grep "<>" | awk \'{print $8*8}\'' % (args.tracefile, args.mac))
    
    paquetesBits = []
    tiempos = []
    count = 0

    for linea in salida.split('\n'):
        if linea != '':
            paquetesBits.append(int(linea))
            tiempos.append(count)
            count += 1

    pintarSerieTemporal(tiempos, paquetesBits, "resultados/ancho_banda_origen.png", "Ancho de banda con MAC como origen", "DD-MM-AAAA hh:mm:ss", "Bits/s")

    #Añadir código para obtener los datos y generar la gráfica de la serie temporal de ancho de banda con MAC como destino
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de la serie temporal de ancho de banda con MAC como destino')
    salida = ejecutarComandoObtenerSalida('tshark -r %s -qz io,stat,1,,eth.dst==%s | grep "<>" | awk \'{print $8*8}\'' % (args.tracefile, args.mac))
    
    paquetesBits = []
    tiempos = []
    count = 0

    for linea in salida.split('\n'):
        if linea != '':
            paquetesBits.append(int(linea))
            tiempos.append(count)
            count += 1

    pintarSerieTemporal(tiempos, paquetesBits, "resultados/ancho_banda_destino.png", "Ancho de banda con MAC como destino", "DD-MM-AAAA hh:mm:ss", "Bits/s")
    
    #Obtención de las ECDF de tamaño de los tiempos entre llegadas
    #Añadir código para obtener los datos y generar la gráfica de la ECDF de los tiempos entre llegadas para el flujo TCP
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de la ECDF de los tiempos entre llegadas para el flujo TCP')
    salida = ejecutarComandoObtenerSalida('tshark -r %s -T fields -e frame.time_delta_displayed -Y \'ip.addr eq %s && tcp.srcport && tcp.dstport\'' % (args.tracefile, args.ip_flujo_tcp))

    tiempos = []
    
    for linea in salida.split('\n'):
        if linea != '':
            tiempos.append(float(linea))

    pintarECDF(tiempos,"resultados/ecdf_tiempos_flujo_tcp.png","Tiempos de llegada del flujo TCP","Tiempo (s)","Porcentaje acumulado de tiempos")

    #Añadir código para obtener los datos y generar la gráfica de la ECDF de los tiempos entre llegadas para el flujo UDP
    logging.info('Ejecutando tshark para obtener los datos y generar la gráfica de la ECDF de los tiempos entre llegadas para el flujo UDP')
    salida = ejecutarComandoObtenerSalida('tshark -r %s -T fields -e frame.time_delta_displayed -Y \'udp.srcport eq %s || udp.dstport eq %s\'' % (args.tracefile, args.port_flujo_udp, args.port_flujo_udp))

    tiempos = []
    
    for linea in salida.split('\n'):
        if linea != '':
            tiempos.append(float(linea))

    pintarECDF(tiempos,"resultados/ecdf_tiempos_flujo_udp.png","Tiempos de llegada del flujo UDP","Tiempo (s)","Porcentaje acumulado de tiempos")
