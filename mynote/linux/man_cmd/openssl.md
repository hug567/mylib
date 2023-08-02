# 1、生成ssl证书和密钥：

```bash
sudo apt install openssl

# 生成一个2048为的私钥：private.key
openssl genpkey -algorithm RSA -out private.key -pkeyopt rsa_keygen_bits:2048
# 使用私钥生成证书请求(CSR)文件：csr.csr
openssl req -new -key private.key -out csr.csr
# 使用私钥和证书请求文件生成一个有效期3650天的自签名证书：certificate.crt
openssl x509 -req -days 3650 -in csr.csr -signkey private.key -out certificate.crt
```

