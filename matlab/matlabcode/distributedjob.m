%demonstrates submiting a distributed matlab job to torque/pbs

sched=findResource('scheduler', 'type', 'torque') 

%set PBS options 'man qsub' for valid options 
%add -l qos=preempt  to use preemption 
%Do NOT set nodes, ppn or tpn 
set(sched, 'SubmitArguments', '-l walltime=15:00 -q cac')

%Create a job  
job1=createJob(sched) 

%add a few tasks, each task will be a one cpu jobs in PBS 
createTask(job1, @rand, 1, {3,3});
createTask(job1, @rand, 1, {3,3});

get(job1, 'Tasks')  

%Submit job and its tasks to the cluster 
submit(job1)  
%you may now exit matlab

