#coding=utf-8
import socket
import time
import sys
 
res_ips = []


def ping(host):
    """
    Returns True if host (str) responds to a ping request.
    Remember that a host may not respond to a ping (ICMP) request even if the host name is valid.
    """
    import platform    # For getting the operating system name
    import subprocess  # For executing a shell command  

    # Option for the number of packets as a function of
    param = '-n' if platform.system().lower()=='windows' else '-c'
    # Building the command. Ex: "ping -c 1 google.com"
    command = ['ping', param, '1', host]
    return subprocess.call(command) == True

def pingIP(ip):
    if ping(ip):
        print('------%s no...-------'% (ip))
    else:
        f = open('./ping_ip_ok.txt', 'a')
        f.write(ip + '\n')
        f.close()
        res_ips.append(ip)
        print('==============%s ok...================='% (ip))

def pingPort(ip, port):
    server = (ip, port)
    sockfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sockfd.settimeout(0.1)
    ret = sockfd.connect_ex(server)  #返回0则成功
    if not ret:
        sockfd.close()
        return True
    else:
        sockfd.close()
        return False

def portScanner(ip, port):

    if pingPort(ip, port):
        f = open('./port_ok.txt', 'a')
        f.write(ip + '\n')
        f.close()
        res_ips.append(ip)
        print('=======%s:%s is opened...========' % (ip, port))
    else:
        print('%s:%s close' % (ip, port))
 
def ip2num(ip):
    lp = [int(x) for x in ip.split('.')]
    return lp[0] << 24 | lp[1] << 16 | lp[2] << 8 |lp[3]
def num2ip(num):
    ip = ['', '', '', '']
    ip[3] = (num & 0xff)
    ip[2] = (num & 0xff00) >> 8
    ip[1] = (num & 0xff0000) >> 16
    ip[0] = (num & 0xff000000) >> 24
    return '%s.%s.%s.%s' % (ip[0], ip[1], ip[2], ip[3])
def iprange(ip1, ip2):
    num1 = ip2num(ip1)
    num2 = ip2num(ip2)
    tmp = num2 - num1
    if tmp < 0:
        return None
    else:
        return num1, num2, tmp
 
 
if __name__ == '__main__':

    if len(sys.argv) < 3 or sys.argv[1] == '-h' or sys.argv[1] == '-help':
        print('\n--------------------------------------------------------')
        print('Usage:')
        print('1 ping ip0 ~ ipn (2 args)')
        print('  ex: ./ping_or_port.py 192.168.0.2 192.168.1.254 ')
        print('\n2 ping and port  (3 args)')
        print('  ex: ./ping_or_port.py 192.168.0.2 192.168.1.254 22')
        print('--------------------------------------------------------\n')
        sys.exit()

    print('start time : %s' % time.ctime(time.time()))
    if len(sys.argv) == 4:
        port = int(sys.argv[3])

    res = ()
    startip = sys.argv[1]
    endip = sys.argv[2]
    res = iprange(startip, endip)

    if not res:
        print('endip must be bigger than startone')
        sys.exit()

    elif len(sys.argv) > 3:         # ip + port 
        for x in range(int(res[2])+1):
            startipnum = ip2num(startip)
            startipnum = startipnum + x
            portScanner(num2ip(startipnum), port)
    else:                           # ip
        for x in range(int(res[2])+1):
            startipnum = ip2num(startip)
            startipnum = startipnum + x
            pingIP(num2ip(startipnum))

    print('end time : %s' % time.ctime(time.time()))
    print(res_ips)
