# 1、虚拟机网络配置：

- VMware虚拟网络组件：虚拟交换机、虚拟网络适配器(虚拟机网卡)、虚拟机DHCP服务器、NAT设备；

## 1)、桥接：

- VMware创建了虚拟交换机VMnet0，与主机网卡通过虚拟网桥通讯，所有虚拟机都连接在虚拟交换机上；
- 虚拟机有独立的ip，与主机在同一子网，网段、网关、DNS等都需与主机一致；

## 2)、NAT：

- VMnet8
- 虚拟机无自己的ip，共享主机的ip，对外通讯是冒用host的ip；

## 3)、仅主机：

- VMnet1

- host新建一个子网，与当前子网不在同一网段，虚拟机连接在host新建的虚拟子网中；