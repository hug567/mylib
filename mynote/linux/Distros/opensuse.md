# 1、openSUSE安装软件：

```shell
zypper lr --detail                                          # 列出软件源
zypper rr <id>                                              # 删除软件源

# 默认官方源
1 | NON OSS         http://download.opensuse.org/distribution/leap/42.3/repo/non-oss/suse/
2 | NON OSS Update  http://download.opensuse.org/update/leap/42.3/non-oss/
3 | OSS             http://download.opensuse.org/distribution/leap/42.3/repo/oss/suse/
4 | OSS Update      http://download.opensuse.org/update/leap/42.3/oss/

# 添加软件源
zypper ar --refresh https://mirrors.cloud.tencent.com/opensuse/distribution/leap/42.3/repo/non-oss/ 'TX NON OSS'
zypper ar --refresh https://mirrors.cloud.tencent.com/opensuse/distribution/leap/42.3/repo/oss/ 'TX OSS'
zypper ar --refresh https://mirrors.cloud.tencent.com/opensuse/update/leap/42.3/non-oss/ 'TX NON OSS Update'
zypper ar --refresh https://mirrors.cloud.tencent.com/opensuse/update/leap/42.3/oss/ 'TX OSS Update'
zypper refresh                                              # 更新软件源

zypper se <name>                                            # 搜索软件
zypper in <name>                                            # 安装软件
zypper rm <name>                                            # 删除软件
zypper up <name>                                            # 更新软件

# opensuse添加语言包
locale                                                      # 查看locale设置
locale -a                                                   # 查看当前locale设置
mv /home/hx/tools/locale-gen /usr/sbin                      # 从宿主机中拷贝一个locale-gen
mv /home/hx/tools/i18n/ /usr/share/                         # 从宿主机拷贝locale文件
vim /etc/locale.gen                                         # 修改locale配置文件
en_US.UTF-8 UTF-8
zh_CN.UTF-8 UTF-8
mkdir -p /usr/lib/locale                                    # 创建保存生成文件目录
locale-gen                                                  # 根据配置文件生成locale
```

