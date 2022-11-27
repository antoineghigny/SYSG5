
sudo bash -c 'echo "deb http://deb.debian.org/debian bullseye main" > /etc/apt/sources.list'
sudo bash -c 'echo "deb-src http://deb.debian.org/debian bullseye main" >> /etc/apt/sources.list'

sudo bash -c 'echo "deb http://deb.debian.org/debian-security/ bullseye-security main" >> /etc/apt/sources.list'
sudo bash -c 'echo "deb-src http://deb.debian.org/debian-security/ bullseye-security main" >> /etc/apt/sources.list'

sudo bash -c 'echo "deb http://deb.debian.org/debian bullseye-updates main" >> /etc/apt/sources.list'
sudo bash -c 'echo "deb-src http://deb.debian.org/debian bullseye-updates main" >> /etc/apt/sources.list'

sudo apt -y update
sudo apt -y install git
sudo apt install make
sudo apt -y install gcc
