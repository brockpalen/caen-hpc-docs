%connects to a job and reads in data

%demonstates reatacching to a finish/unfinished job and reading tasks and their results
%this assumes one job with atleast two tasks. 
%There are better ways to read 'a task at a time' if all tasks are to large to fit in memory
sched=findResource('scheduler', 'type', 'torque')

job = findJob(sched)
tasks = findTask(job)
results = getAllOutputArguments(job)

results{1,1}
results{2,1}
