# Morel
A monthly expenses calculator CLI application for generating customized monthly expense reports

## Installation

### Using Linux?
1. Open a terminal
2. Install dependencies
```
sudo apt-get install git libboost-all-dev cmake make g++
```
3. clone the repo inside of the Ubuntu environment
```
git clone https://github.com/b-nagaj/Morel.git
```

### Using Windows?
Morel is native to linux environments. Here's how to use the app with the Windows Subsystem for Linux (WSL)
1. Open a Windows powershell as an administrator
```
wsl --install
```
2. Restart your machine and open windows powershell as an administrator
```
wsl --install -d Ubuntu
```
3. Follow the prompts inside of Ubuntu to enter a UNIX username and password
4. Ensure that you are inside your user's home directory (i.e. /home/yourUsername)
5. Install dependencies
```
sudo apt-get install git libboost-all-dev cmake make g++
```
6. clone the repo inside of the Ubuntu environment
```
git clone https://github.com/b-nagaj/Morel.git
```
## Usage
```
cmake . 
make
./Morel
```
