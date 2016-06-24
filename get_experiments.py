"""
parses through log file
pulls out logs that contain experiments
and writes them to own file
"""
import urllib
import pickle

experiment_list = []

with open('access.log.10') as data:

	for each_line in data:
		"""if line contains 'experiments'"""
		if not each_line.find('experiments') == -1:
			if not each_line.find('?set=') == -1:
				entry={}
				idx=each_line.find(' ')
				IP=each_line[0:idx]
				#print(IP)
				idx0=each_line.find('[')
				idx1=each_line.find(']')
				date=each_line[idx0:idx1+1]
				#print(date)
				idx0=each_line.find('"')
				idx1=each_line.find('"', idx0+1)
				url=each_line[idx0:idx1+1]
				#print(url)
				entry['IP']=IP
				entry['date']=date
				(get, superstar, school, robot, experiment, experiment_name, code) = url.split('/', 6)
				#print(get)
				#print(superstar)
				#print(school)
				#print(robot)
				#print(experiment)
				#print(experiment_name)
				#print(code)
				entry['school']=school
				entry['robot']=robot
				entry['experiment_name']=experiment_name
				start_idx=code.find('=')
				end_idx=code.find(' ', start_idx+1)
				striped_code=code[start_idx+1:end_idx]
				decoded_striped_code=urllib.unquote(striped_code).decode('utf8')
				entry['code']=decoded_striped_code
				#determine number of states in code
				#?what if students use 'name' in their code?
				num_states=decoded_striped_code.count("name")
				entry['num_states']=num_states
				experiment_list.append(entry)
				
"""write list of experiments to file"""
with open('experiment_pickle.txt', 'wb') as file_out:
					pickle.dump(experiment_list, file_out)
print("number of experiments pickled:")
print(len(experiment_list))

with open('experiment_pickle.txt', 'rb') as in_file:
	unpickled_experiments=pickle.load(in_file)
	for each_entry in unpickled_experiments:
		print(each_entry)
print("number of experiments unpickled:")
print(len(unpickled_experiments))
					


file_out.close()
in_file.close()
data.close()