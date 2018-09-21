#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import getopt, sys, os, ConfigParser, subprocess, time
import json, string, random

class Leminode_VM:
    def __init__(self):
        self.name = ""
        self.conf_file = ""
        self.vm_config = {"mem":"", "vcpu":0, "disk":"", "network":""}

    def set_name(self, vm_name):
        self.name = vm_name

    def __exec_command(self, cmd):
        try:
            output = subprocess.check_output(cmd.split(" "))
            if output.find("error") > 0:
                return False
        except Exception, ex:
            return False
        return True

    def __post_create_pf(self, vm_idx, port):
        addresses = None
        ip = None
        pport=10000 + vm_idx * 100 + port
        vms = subprocess.check_output("lxc list --format=json".split(" "))
        for vm in json.loads(vms):
            if vm["name"] == self.name:
                addresses = vm["state"]["network"]["eth0"]["addresses"]
                break
        for addr in addresses:
            if addr["family"] == "inet":
                ip = addr["address"]
                break
        cmd='echo "111111" | sudo -S iptables -t nat -A PREROUTING -p tcp -i eno1 --dport {0} -j DNAT --to-destination {1}:{2}'.format(pport, ip, port)
        os.system(cmd)
        time.sleep(3)
        return pport

    def __post_delete_pf(self, vm_idx, port):
        addresses = None
        ip = None
        pport=10000 + vm_idx * 100 + port
        vms = subprocess.check_output("lxc list --format=json".split(" "))
        for vm in json.loads(vms):
            if vm["name"] == self.name:
                if vm["status"] == "Running":
                    addresses = vm["state"]["network"]["eth0"]["addresses"]
                    break
                else:
                    return True
        if addresses is None:
            return True
        for addr in addresses:
            if addr["family"] == "inet":
                if "address" in addr:
                    ip = addr["address"]
                    break
                else:
                    return True
        cmd='echo "111111" | sudo -S iptables -t nat -D PREROUTING -p tcp -i eno1 --dport {0} -j DNAT --to-destination {1}:{2}'.format(pport, ip, port)
        os.system(cmd)
        time.sleep(3)
        return True

    def __post_ubuntu_config(self, rpassword):
        os.system('echo "apt-get install openssh-server -y" | lxc exec {0} "/bin/bash"'.format(self.name))
        os.system('echo "sed -i s/#PermitRootLogin/PermitRootLogin/g /etc/ssh/sshd_config" | lxc exec {0} "/bin/bash"'.format(self.name))
        os.system('echo "sed -i s/#PasswordAuthentication/PasswordAuthentication/g /etc/ssh/sshd_config" | lxc exec {0} "/bin/bash"'.format(self.name))
        os.system('echo "sed -i s/without-password/yes/g /etc/ssh/sshd_config" | lxc exec {0} "/bin/bash"'.format(self.name))
        os.system('echo "sed -i s/prohibit-password/yes/g /etc/ssh/sshd_config" | lxc exec {0} "/bin/bash"'.format(self.name))
        os.system('echo "sed -i s/PasswordAuthentication\ no/PasswordAuthentication\ yes/g /etc/ssh/sshd_config" | lxc exec {0} "/bin/bash"'.format(self.name))
        os.system('echo "hostname {0}" | lxc exec {0} "/bin/bash"'.format(self.name))
        time.sleep(1)
        os.system('echo "/etc/init.d/ssh restart" | lxc exec {0} "/bin/bash"'.format(self.name))
        os.system('echo "hostname {0}"| lxc exec {0} "/bin/bash"'.format(self.name))
        os.system('echo "{0}\n{0}" | lxc exec {1} "passwd"'.format(rpassword, self.name))
        time.sleep(2)

    def __post_centos_config(self, rpassword):
        os.system('echo "yum -y install openssh-server" | lxc exec {0} "/bin/bash"'.format(self.name))
        time.sleep(40)
        os.system('echo "sed -i s/#PermitRootLogin/PermitRootLogin/g /etc/ssh/sshd_config" | lxc exec {0} "/bin/bash"'.format(self.name))
        time.sleep(1)
        os.system('echo "service sshd restart" | lxc exec {0} "/bin/bash"'.format(self.name))
        os.system('echo "chkconfig sshd on" | lxc exec {0} "/bin/bash"'.format(self.name))
        os.system('echo "{0}\n{0}" | lxc exec {1} "passwd"'.format(rpassword, self.name))
        time.sleep(2)

    def __post_fedora_config(self, rpassword):
        os.system('echo "dnf --nogpgcheck -y install openssh-server" | lxc exec {0} "/bin/bash"'.format(self.name))
        time.sleep(40)
        os.system('echo "service sshd restart" | lxc exec {0} "/bin/bash"'.format(self.name))
        os.system('echo "chkconfig sshd on" | lxc exec {0} "/bin/bash"'.format(self.name))
        os.system('echo "{0}\n{0}" | lxc exec {1} "passwd"'.format(rpassword, self.name))
        time.sleep(2)

    def __post_create_vm(self, vm_os, vm_profile, rpassword):
        os_full_name = ""
        if vm_os == "u14":
            os_full_name = "ubuntu14.04"
        elif vm_os == "u16":
            os_full_name = "ubuntu16.04"
        elif vm_os == "u18":
            os_full_name = "ubuntu18.04"
        elif vm_os == "c7":
            os_full_name = "centos7"
        elif vm_os == "c6":
            os_full_name = "centos6"
        elif vm_os == "f23":
            os_full_name = "fedora23"
        elif vm_os == "f24":
            os_full_name = "fedora24"
        elif vm_os== "infrasim":
            os_full_name = "infrasim"
        else:
            pass
        self.__exec_command("lxc launch {0} {1} -p {2}".format(os_full_name, self.name, vm_profile))
        #self.__exec_command("lxc config set {0} limits.cpu {1}".format(self.name, self.vm_config["vcpu"]))
        #self.__exec_command("lxc config set {0} limits.memory {1}".format(self.name, self.vm_config["mem"]))
        #self.__exec_command("lxc config set {0} limits.memory.enforce hard".format(self.name))
        #self.__exec_command("lxc config set {0} limits.memory.swap false".format(self.name))
        #self.__exec_command("lxc config set {0} security.nesting true".format(self.name))
        #self.__exec_command("lxc config set {0} security.privileged true".format(self.name))
        #self.__exec_command("lxc config device set {0} root size {1}".format(self.name, self.vm_config["disk"]))
        #self.__exec_command("lxc config device add {0} tun unix-char path=/dev/net/tun".format(self.name))
        #self.__exec_command("lxc config device add {0} kvm unix-char path=/dev/kvm".format(self.name))
        time.sleep(10)
        if os_full_name.find("ubuntu") >= 0:
            self.__post_ubuntu_config(rpassword)
        elif os_full_name.find("centos") >= 0:
            self.__post_centos_config(rpassword)
        elif os_full_name.find("fedora") >= 0:
            self.__post_fedora_config(rpassword)
        elif os_full_name.find("infrasim") >= 0:
            self.__post_ubuntu_config(rpassword)
        else:
            pass

    def __post_delete_vm(self):
        os.system('echo "" > ' + self.conf_file)
        return self.__exec_command("lxc delete {0} --force".format(self.name))

    def __post_start_vm(self):
        res = self.__exec_command("lxc start {0}".format(self.name))
        time.sleep(10)
        return res

    def __post_stop_vm(self):
        res = self.__exec_command("lxc stop {0} --force".format(self.name))
        time.sleep(5)
        return res

    def add_port(self, vm_idx, port):
        return self.__post_create_pf(vm_idx, port)

    def del_port(self, vm_idx, port):
        return self.__post_delete_pf(vm_idx, port)

    def create_vm(self, vm_idx, vm_name, vm_os, vm_profile):
        self.vm_config["mem"] = "2048MB"
        self.vm_config["vcpu"] = 4
        self.vm_config["disk"] = "40GB"
        self.vm_config["network"] = "1T"
        self.conf_file = os.environ["HOME"] + "/.leminode/vm_{0}.conf".format(vm_idx)
        self.name = vm_name

        config = ConfigParser.RawConfigParser()
        config.add_section("node")
        config.set("node", "name", self.name)
        config.set("node", "mem", self.vm_config["mem"])
        config.set("node", "vcpu", self.vm_config["vcpu"])
        config.set("node", "disk", self.vm_config["disk"])
        config.set("node", "network", self.vm_config["network"])
        config.set("node", "os", vm_os)
        config.set("node", "sshport", 22)
        config.set("node", "vncport", 5901)
        rpassword = ''.join(random.choice(string.ascii_uppercase + string.digits + string.ascii_lowercase) for _ in range(8))
        config.set("node", "rpassword", rpassword)
        with open(self.conf_file, 'wb') as f:
            config.write(f)

        self.__post_create_vm(vm_os, vm_profile, rpassword)
        #self.__post_create_pf(vm_idx, 22)
        #self.__post_create_pf(vm_idx, 5901)
        return json.dumps({"status":"success"})

    def delete_vm(self, vm_idx):
        conf = ConfigParser.ConfigParser()
        self.conf_file = os.environ["HOME"] + "/.leminode/vm_{0}.conf".format(vm_idx)
        conf.read(self.conf_file)
        self.name = conf.get("node", "name")

        #res = self.__post_delete_pf(vm_idx, 22)
        #res = self.__post_delete_pf(vm_idx, 5901)
        res = self.__post_delete_vm()
        if res is True:
            return json.dumps({"status":"success"})

        return json.dumps({"status":"failed"})

    def start_vm(self, vm_idx):
        conf = ConfigParser.ConfigParser()
        self.conf_file = os.environ["HOME"] + "/.leminode/vm_{0}.conf".format(vm_idx)
        conf.read(self.conf_file)
        self.name = conf.get("node", "name")

        self.__post_start_vm()
        #self.__post_create_pf(vm_idx, 22)
        #self.__post_create_pf(vm_idx, 5901)
        return json.dumps({"status":"success"})

    def stop_vm(self, vm_idx):
        conf = ConfigParser.ConfigParser()
        self.conf_file = os.environ["HOME"] + "/.leminode/vm_{0}.conf".format(vm_idx)
        conf.read(self.conf_file)
        self.name = conf.get("node", "name")

        #self.__post_delete_pf(vm_idx, 22)
        #self.__post_delete_pf(vm_idx, 5901)
        self.__post_stop_vm()
        return json.dumps({"status":"success"})

def get_available_vm(vm_name):
    for i in range(0, 200):
        conf = ConfigParser.ConfigParser()
        conf.read(os.environ["HOME"] + "/.leminode/vm_{0}.conf".format(i + 1))
        if conf.has_option("node", "name") is True:
            if conf.get("node", "name") is "":
                return i + 1
            if vm_name == conf.get("node", "name"):
                return -1
            else:
                continue
        else:
            return i + 1
    return -2

def find_vm(vm_name):
    for i in range(0, 200):
        conf = ConfigParser.ConfigParser()
        conf.read(os.environ["HOME"] + "/.leminode/vm_{0}.conf".format(i + 1))
        if conf.has_option("node", "name") is True:
            if conf.get("node", "name") == vm_name:
                return i + 1
    return -1

def leminode_init():
    if os.path.exists(os.environ["HOME"] + "/.leminode") is True:
        print "Leminode inited already!"
        return

    conf_dir = os.environ["HOME"] + "/.leminode"
    os.mkdir(os.environ["HOME"] + "/.leminode")
    for i in range(0,200):
        os.system("touch {0}/vm_{1}.conf".format(conf_dir, i + 1))
    print "Leminode init successfully"

def leminode_create_vm(vm_name, os, profile):
    result = get_available_vm(vm_name)
    if result < 0:
        if result == -2:
            print "can't find available vm"
        elif result == -1:
            print "VM name is already created"
        return

    vm = Leminode_VM()
    print vm.create_vm(result, vm_name, os, profile)

def leminode_start_vm(vm_name):
    result = find_vm(vm_name)
    if result < 0:
        print "Can't find VM: {}".format(vm_name)
        return

    vm = Leminode_VM()
    print vm.start_vm(result)

def leminode_stop_vm(vm_name):
    result = find_vm(vm_name)
    if result < 0:
        print "Can't find VM: {}".format(vm_name)
        return

    vm = Leminode_VM()
    print vm.stop_vm(result)

def leminode_delete_vm(vm_name):
    result = find_vm(vm_name)
    if result < 0:
        print "Can't find VM: {}".format(vm_name)
        return

    vm = Leminode_VM()
    print vm.delete_vm(result)

def leminode_list_vm():
    os.system("lxc list")

def leminode_info_vm(vm_name):
    idx = find_vm(vm_name)
    if idx < 0:
        print json.dumps({"status":"failed", "msg":"can't find VM"})
        return

    vm_info = {"name":vm_name}
    conf = ConfigParser.ConfigParser()
    conf.read(os.environ["HOME"] + "/.leminode/vm_{0}.conf".format(idx))
    vm_info["vcpu"] = conf.get("node", "vcpu")
    vm_info["memory"] = conf.get("node", "mem")
    vm_info["disk"] = conf.get("node", "disk")
    vm_info["network"] = conf.get("node", "network")
    vm_info["os"] = conf.get("node", "os")
    vm_info["rpassword"] = conf.get("node", "rpassword")
    vm_info["ssh"] = int(conf.get("node", "sshport")) + 10000 + idx * 100
    vm_info["vnc"] = int(conf.get("node", "vncport")) + 10000 + idx * 100
    
    lines = subprocess.check_output(("lxc info {}".format(vm_name)).split(" "))
    for line in lines.split("\n"):
        if string.find(line, "Status") >= 0:
            vm_info["status"] = line.split(":")[1].strip()
        if string.find(line, "Created") >= 0:
            vm_info["created"] = line.split(":")[1].strip()
        if string.find(line, "Profiles") >= 0:
            vm_info["profile"] = line.split(":")[1].strip()
    nics = {}
    networks={"eth0":"default"}
    statistic = {}
    vms = subprocess.check_output(("lxc list {} --format=json".format(vm_name)).split(" "))

    for vm in json.loads(vms):
        if vm[u"name"] == vm_name:
            try:
                for key in vm[u"state"][u"network"].keys():
                    if key == "lo":
                        continue
                    nics[key.encode("utf-8")] = vm[u"state"][u"network"][key][u"addresses"][0][u"address"]
            except Exception, e:
                pass
            if vm[u"expanded_devices"].has_key(u"eth1"):
                networks["eth1"] = vm[u"expanded_devices"][u"eth1"][u"parent"]
            if vm[u"expanded_devices"].has_key(u"eth2"):
                networks["eth2"] = vm[u"expanded_devices"][u"eth2"][u"parent"]
            if vm[u"state"] is not None:
	        statistic["disk"] = int(vm[u"state"][u"disk"][u"root"][u"usage"])/1024/1024
            else:
                statistic["disk"] = 0
	    if vm[u"state"] is not None:
                statistic["memory"] = int(vm[u"state"][u"memory"][u"usage"])/1024/1024
            else:
                statistic["memory"] = 0
    vm_info["nics"] = nics
    vm_info["networks"] = networks
    vm_info["statistic"] = statistic
    print json.dumps({"status":"success", "vm_info":vm_info})

def leminode_cap_vm():
    vm_cap = {"mem":0, "vcpu":0, "disk":0, "network":0}
    for i in range(0, 200):
        conf = ConfigParser.ConfigParser()
        conf.read(os.environ["HOME"] + "/.leminode/vm_{0}.conf".format(i + 1))
        if conf.has_option("node", "name") is True:
            vm_cap["mem"] = vm_cap["mem"] + int(conf.get("node", "mem")[:-2])
            vm_cap["disk"] = vm_cap["disk"] + int(conf.get("node", "disk")[:-2])
            vm_cap["network"] = vm_cap["network"] + int(conf.get("node", "network")[:-2])

    print vm_cap

def leminode_addport(vm_name, port):
    idx = find_vm(vm_name)
    if idx < 0:
        print json.dumps({"status":"failed", "msg":"can't find VM"})
        return
    print json.dumps({"status":"success", "msg":str(10000 + idx * 100 + int(port))})
    
def leminode_startport(vm_name, port):
    idx = find_vm(vm_name)
    if idx < 0:
        print json.dumps({"status":"failed", "msg":"can't find VM"})
        return

    vm = Leminode_VM()
    vm.set_name(vm_name)
    vm.add_port(idx, int(port))
    print json.dumps({"status":"success"})

def leminode_stopport(vm_name, port):
    idx = find_vm(vm_name)
    if idx < 0:
        print json.dumps({"status":"failed", "msg":"can't find VM"})
        return

    vm = Leminode_VM()
    vm.set_name(vm_name)
    vm.del_port(idx, int(port))
    print json.dumps({"status":"success"})
 
def leminode_addbr(br_name, br_address):
    cmds = []
    cmds.append('echo "111111" | sudo -S brctl addbr {} '.format(br_name))
    cmds.append('echo "111111" | sudo -S brctl setfd {} 0'.format(br_name))
    cmds.append('echo "111111" | sudo -S brctl sethello {} 1'.format(br_name))
    cmds.append('echo "111111" | sudo -S brctl stp {} no'.format(br_name))
    br_inter = br_address.split('.')
    br_ip = br_address
    br_netmask = "255.255.255.0"
    br_network = '.'.join(br_inter[:3]) + '.0'
    br_gw = '.'.join(br_inter[:3]) + '.1'
    br_bcast = '.'.join(br_inter[:3]) + '.255'
    #cmds.append('echo "infrasim" | sudo -S ifconfig {0} {1} netmask {2} gw {3} up'.format(br_name, br_ip, br_netmask, br_gw))
    cmds.append('echo "111111" | sudo -S ifconfig {0} up'.format(br_name))
    cmds.append('echo "111111" | sudo -S lxc profile copy infrasim {}'.format(br_name))
    cmds.append('echo "111111" | sudo -S lxc profile device add {0} eth1 nic name=eth1 parent={0} nictype=bridged'.format(br_name))
    for cmd in cmds:
        os.system(cmd)
    print json.dumps({"status":"success"})

def leminode_delbr(br_name):
    cmds = []
    cmds.append('echo "111111" | sudo -S lxc profile delete {}'.format(br_name))
    cmds.append('echo "111111" | sudo -S ifconfig {} down '.format(br_name))
    cmds.append('echo "111111" | sudo -S brctl delbr {} '.format(br_name))
    for cmd in cmds:
        os.system(cmd)
    print json.dumps({"status":"success"})

def main_help():
    if sys.argv[1] == "help":
        print "Usage: {0} [subcommand] [option]\nAvailable commands:".format(sys.argv[0])
        print "\tinit	- init leminode environment"
        print "\tcreate	- create vm on host"
        print "\tstart	- start vm on host"
        print "\tstop	- stop vm on host"
        print "\tdelete	- delete vm on host"
        print "\tlist	- list vms"
        print "\tinfo	- show vms info in json format"
        print "\tcap	- Get Host lxd capacity"
        print "\taddbr	- Add a brdige for container"
        print "\tstartport	- Start a port mapping for container"
        print "\tdelbr	- Delete a bridge for container"
        print "\tstopport	- Stop a port mapping for container"
    elif sys.argv[1] == "init":
        leminode_init()
    elif sys.argv[1] == "create":
        leminode_create_vm(sys.argv[2], sys.argv[3], sys.argv[4])
    elif sys.argv[1] == "start":
        leminode_start_vm(sys.argv[2])
    elif sys.argv[1] == "stop":
        leminode_stop_vm(sys.argv[2])
    elif sys.argv[1] == "delete":
        leminode_delete_vm(sys.argv[2])
    elif sys.argv[1] == "list":
        leminode_list_vm()
    elif sys.argv[1] == 'info':
        leminode_info_vm(sys.argv[2])
    elif sys.argv[1] == "cap":
        leminode_cap_vm()
    elif sys.argv[1] == "addbr":
        leminode_addbr(sys.argv[2], sys.argv[3])
    elif sys.argv[1] == "delbr":
        leminode_delbr(sys.argv[2])
    elif sys.argv[1] == "addport":
        leminode_addport(sys.argv[2], sys.argv[3])
    elif sys.argv[1] == "startport":
        leminode_startport(sys.argv[2], sys.argv[3])
    elif sys.argv[1] == "stopport":
        leminode_stopport(sys.argv[2], sys.argv[3])
    else:
        pass

if __name__=="__main__":
    main_help()
