#!/usr/bin/env python

"""
    This script is  for io translate the ftrace to chrome known formate and can open it in chorme://tracing 
    Shall be has the below event 
     echo sched:sched_wakeup >> /sys/kernel/debug/tracing/set_event
     echo sched:sched_switch >> /sys/kernel/debug/tracing/set_event
     echo 1 > /sys/kernel/debug/tracing/events/power/cpu_idle/enable
     echo 1 >/sys/kernel/debug/tracing/events/irq/enable

"""

import os
import sys
import re
import time

from collections import OrderedDict

newLines = []
appNamePID=OrderedDict()

HEADER=[
'# tracer: nop\n',
'#\n',
'# entries-in-buffer/entries-written: 37199/37199   #P:8\n',
'#\n',
'#                                      _-----=> irqs-off\n',
'#                                     / _----=> need-resched\n',
'#                                    | / _---=> hardirq/softirq\n',
'#                                    || / _--=> preempt-depth\n',
'#                                    ||| /     delay\n',
'#           TASK-PID    TGID   CPU#  ||||    TIMESTAMP  FUNCTION\n'
]


FtraceHeader='# tracer: nop'


def processFtraceline2Chromeknown(ftraceline):
    filed2=' d..2 '
    FirstcolumnLenth=28
    if ftraceline is None:
        return 
    # python3-13377 [005] dn..2.. 184555.267704: sched_wakeup: comm=ktimersoftd/5 pid=60 prio=98 target_cpu=005  //NV frace  handle this ftrace
    #<...>-9419  ( 9419) [005] d..1 25132.457856: mm_filemap_delete_from_page_cache: dev 253:6 ino 1 page=0000000012dc0ac3 pfn=1106859 ofs=29962240 //normal 
    #rule="([^\s].*?)-(\d+)\s+\(\s*([0-9-]+)\)\s+\[\d+\]\s+[^\s]+\s+(\d+\.\d+):\s"+keyword+":\s+([^\s].*?)$" Non NV ftrace 
    rule="([^\s].*?-\d+\s+\[\d+\])\s+([^\s].*?)+\s([^\s].*?)$"
    args = re.findall(rule, ftraceline)
    #print("Exit %s" % line)
    #print("args %s" % args)
    if(args is not None and len(args)!=0):  
      line=args[0][0].rjust(FirstcolumnLenth)+filed2+args[0][2]+"\n"
      return line
    return 
def processFtraceline2ChromeknownwithoutPID(ftraceline):
    filed2=' d..2 '
    groupFiled=' ('
    groupIdle=' (-----) '
    idle='idle'
    FirstcolumnLenth=28
    if ftraceline is None:
        return 
    # python3-13377 [005] dn..2.. 184555.267704: sched_wakeup: comm=ktimersoftd/5 pid=60 prio=98 target_cpu=005  //NV frace  repare the threadgroup 
    #<...>-9419  ( 9419) [005] d..1 25132.457856: mm_filemap_delete_from_page_cache: dev 253:6 ino 1 page=0000000012dc0ac3 pfn=1106859 ofs=29962240 //normal 
    # <...>-1904  ( 1904) [004] .... 1916086.826955: tracing_mark_write: E|1904
    # <idle>-0    (-----) [006] d..1 1916086.826990: cpu_idle: state=0 cpu_id=6
    #rule="([^\s].*?)-(\d+)\s+\(\s*([0-9-]+)\)\s+\[\d+\]\s+[^\s]+\s+(\d+\.\d+):\s"+keyword+":\s+([^\s].*?)$" Non NV ftrace 
    #rule="([^\s].*?-\d+\s+\[\d+\])\s+([^\s].*?)+\s([^\s].*?)$"
    rule="([^\s].*?)-(\d+)\s+(\[\d+\])\s+([^\s].*?)+\s([^\s].*?)$"
    args = re.findall(rule, ftraceline)
    #print("args %s" % args)
    #print("ftraceline %s" % ftraceline)
    '''
    python3-13377 [005] dn..2.. 184555.267704: sched_wakeup: comm=ktimersoftd/5 pid=60 prio=98 target_cpu=005
    args[0][0]: python3
    args[0][1]: 13377
    args[0][2]: [005] 
    args[0][4]: 184555.267704: sched_wakeup: comm=ktimersoftd/5 pid=60 prio=98 target_cpu=005

    '''
    groupFiled=''
    if(args is not None and len(args)!=0):  
      if(args[0][0].find(idle)>=0):
          groupFiled=groupIdle
      else:
          if(appNamePID.has_key(args[0][0])==False):
              appNamePID[args[0][0]]=args[0][1]
          pid=appNamePID.get(args[0][0])
          groupFiled=' ('+pid.rjust(5)+') '
      line=(args[0][0]+'-'+args[0][1]).rjust(FirstcolumnLenth)+groupFiled+args[0][2]+filed2+args[0][4]+"\n"
      return line
    return 
def hasPID(ftraceline):
    if ftraceline is None:
        return 
    # ksoftirqd/0-8     (    8) [000] .....12 248988.247408: softirq_entry: vec=7 [action=SCHED] //NV frace  handle this ftrace
    rulepid="([^\s].*?-\d+)\s+(\(\s*[0-9-]+\))\s"
    args = re.findall(rulepid, ftraceline)
    if(args is not None and len(args)!=0):  
      return True
    return False
def processFtraceline2ChromeknownwithPID(ftraceline):
    filed2=' d..2 '
    FirstcolumnLenth=42
    if ftraceline is None:
        return 
    # ksoftirqd/0-8     (    8) [000] .....12 248988.247408: softirq_entry: vec=7 [action=SCHED] //NV frace  handle this ftrace
    rule="([^\s].*?-\d+\s+\(\s*[0-9-]+\)\s+\[\d+\])\s+[^\s]+\s+(\d+\.\d+:\s+[^\s].*?)$"
    args = re.findall(rule, ftraceline)
    #print("Exit %s" % ftraceline)
    #print("args %s" % args)
    if(args is not None and len(args)!=0):  
      line=args[0][0].rjust(FirstcolumnLenth)+filed2+args[0][1]+"\n"
      return line
    return 
def postProcessing(lines):
    global newLines
    #Add Header 
    newLines.append(''.join(HEADER))
    #print(newLines)
    '''
    if(NeedInserHeader(lines[0])):
        print("has no header.....")
        newLines.append(HEADER)
    '''
    knowFormate=False
    skipFirstline=False
    for line in lines:
        if(line is not None):
            if(line.startswith('#')):
                continue
        if(knowFormate==False):
            #skip first line
            if(skipFirstline==False):
                skipFirstline=True
                continue
            pid=hasPID(line)
            knowFormate=True
        if(pid):
            postLine=processFtraceline2ChromeknownwithPID(line)
        else:
            postLine=processFtraceline2ChromeknownwithoutPID(line)
        if(postLine is not None):
           newLines.append(postLine)
    return newLines

if __name__ == "__main__":
    

    startTime = time.time()
    '''
    if sys.version_info >= (3,0):
        print(" Please use Python 2.7.")
        sys.exit(0)
    '''
    if len(sys.argv) < 2:
        print("Please input the ftrace file")
        sys.exit(0)

    fp = open(sys.argv[1])
    lines = fp.readlines()
    newLines = postProcessing(lines)
    
    fout, ext = os.path.splitext(sys.argv[1])
    fout = open(fout + "_2chrome" + ext, "wb")
    #newlines.remove(newlines[len(newlines)-1])
    removeLastLine=newLines[:-1]
    fout.writelines(removeLastLine)
    print("Post-processing took %.2f seconds" % (time.time() - startTime))
   
    
