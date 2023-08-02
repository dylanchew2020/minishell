
bash: export: `ee e=123': not a valid identifier - handled
$asdasd - handled
export $=2 - handled
export "hi world"=a - handled
export hi=bye bye=hi hi=test - handled
unclosed quote leak - handled
check all ft_strncmp -checked

export a - handled


% ls -l | grep ".txt" > txt_files.txt
% sort < input.txt | uniq > sorted_uniq.txt
% ls -l | grep ".txt" >> existing_file.txt
% cat file.txt | tr '[:lower:]' '[:upper:]' | sort > sorted_caps.txt

% cat << EOF | sort > sorted_input.txt
% orange
% apple
% banana
% EOF

% sort < input.txt | uniq >> existing_sorted_uniq.txt

% cat < input.txt | tr '[:lower:]' '[:upper:]' | sort > sorted_caps.txt

% cat << EOF | tr '[:lower:]' '[:upper:]' | sort > sorted_caps.txt
% orange
% apple
% banana
% EOF

% sort < input.txt | uniq -c >> existing_sorted_uniq_counts.txt

% cat << EOF | tr '[:lower:]' '[:upper:]' | sort >> existing_sorted_caps.txt
% orange
% apple
% banana
% EOF

% cat << a > test1 | rev << b >> test1