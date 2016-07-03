import time
import httplib
import urllib

IP = "http://192.168.8.162"
def send2ESP(status):
   '''
   httpServ = httplib.HTTPConnection("192.168.8.137", 80)
   httpServ.connect()
   request = "gpio/" + str(status)
   httpServ.request('GET', request)
   print 'sent request to ESP'
   httpServ.close()
   '''
   urllib.urlopen(IP+"/gpio/"+str(status))


flag = 0

while True:
    try:
        fp = open("PSIM_out.dat","r")
        f = fp.readline()
        dr = fp.readline()
        fp.close()
        relay_control_variable = float(dr)
        print "relay control var"
        print relay_control_variable
        frequency = float(f)
        print "frequency"
        print frequency
    except:
        print "error"
    if relay_control_variable < 500:
        if flag == 0:
            print "sending"
            send2ESP(0)
        flag = 1
    elif relay_control_variable > 500:
        if flag == 1:
            print "sending"
            send2ESP(1)
        flag = 0
    time.sleep(.09)
