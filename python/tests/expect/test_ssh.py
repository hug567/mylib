#!/usr/bin/python3
# python expect库
import pexpect

child = pexpect.spawn('ssh root@192.168.0.2')
child.expect('password:')
print(child.before)

child.sendline('root')
child.expect('root@')
print(child.before)

child.sendline('ls -l /')
child.expect('root@')
print(child.before)

#child.interact()
