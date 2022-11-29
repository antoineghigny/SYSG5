
sudo bash -c 'deb http://security.debian.org/debian-security buster/updates main contrib" >> /etc/apt/sources.list'
sudo bash -c 'deb-src http://security.debian.org/debian-security buster/updates main contrib" >> /etc/apt/sources.list'

sudo bash -c 'deb http://deb.debian.org/ buster-updates main contrib" >> /etc/apt/sources.list'
sudo bash -c 'deb-src http://ftp.debian.org/debian/ buster main contrib" >> /etc/apt/sources.list'

sudo apt -y update
sudo apt -y install git
sudo apt install make
sudo apt -y install gcc
