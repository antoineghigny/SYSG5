
sudo bash -c 'echo "deb http://security.debian.org/debian-security buster/updates main contrib" > /etc/apt/sources.list'
sudo bash -c 'echo "deb-src http://security.debian.org/debian-security buster/updates main contrib" >> /etc/apt/sources.list'

sudo bash -c 'echo "deb http://deb.debian.org/debian/ buster-updates main contrib" >> /etc/apt/sources.list'
sudo bash -c 'echo "deb-src htp://deb.debian.org/debian/ buster-updates main contrib" >> /etc/apt/sources.list'


sudo bash -c 'echo "deb http://ftp.debian.org/debian/ buster main contrib" >> /etc/apt/sources.list'
sudo bash -c 'echo "deb-src http://ftp.debian.org/debian/ buster main contrib" >> /etc/apt/sources.list'

sudo apt -y update
sudo apt -y install git
sudo apt install make
sudo apt -y install gcc
