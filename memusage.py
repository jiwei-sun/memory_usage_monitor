#!/usr/bin/python
import sys
import pygal

f = open(str(sys.argv[1]))
vmsize_lst = []
vmrss_lst = []

task_name = f.readline()
begin_time = f.readline()
interval_time = f.readline()

while True:
    line = f.readline()
    if not line: break
    if "VmSize:" in line:
        s_tmp=line[7:16]
	s=s_tmp.strip()
	vmsize_lst.append(long(s))
    if "VmRSS:" in line:
        s_tmp=line[6:16]
	s=s_tmp.strip()
	vmrss_lst.append(long(s))
f.close()

line_chart = pygal.Line()
line_chart.title = task_name + 'Memory usage (in KB),' + begin_time + interval_time
line_chart.add('VmSize',  vmsize_lst)
line_chart.add('VmRSS', vmrss_lst)
line_chart.render_to_file('memory_usage.svg')
