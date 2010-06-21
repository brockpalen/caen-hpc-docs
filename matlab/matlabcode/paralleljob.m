%creates a parallel job and submits colsum.m as a parallel job on 4 cpus

%create parallel sched object
sched=findResource('scheduler', 'type', 'torque')
%set PBS options 'man qsub' for valid options
%add -l qos=preempt  to use preemption
%Do NOT set nodes, ppn or tpn
set(sched, 'SubmitArguments', '-l walltime=15:00 -q cac -M brockp@umich.edu -m abe')
	
%create parallel job, set the number of CPUs to use
pjob=createParallelJob(sched);
set(pjob, 'MaximumNumberOfWorkers', 4)
set(pjob, 'MinimumNumberOfWorkers', 4)
%create parallel taks using colsum.m from above
set(pjob, 'FileDependencies', {'colsum.m'})
t=createTask(pjob, @colsum, 1, {})
%submit 10 cpu PBS job
submit(pjob)
waitForState(pjob)
results=getAllOutputArguments(pjob)
destroy(pjob)

