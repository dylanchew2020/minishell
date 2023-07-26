echo -nn "Hello, World!"
echo -n -n "Hello, World!"

exit status
$?

unset first env node

echo hi > 1.tmp test

ls -l | grep ".txt" > txt_files.txt
sort < input.txt | uniq > sorted_uniq.txt
ls -l | grep ".txt" >> existing_file.txt
cat file.txt | tr '[:lower:]' '[:upper:]' | sort > sorted_caps.txt

cat << EOF | sort > sorted_input.txt
orange
apple
banana
EOF

sort < input.txt | uniq >> existing_sorted_uniq.txt

cat < input.txt | tr '[:lower:]' '[:upper:]' | sort > sorted_caps.txt

cat << EOF | tr '[:lower:]' '[:upper:]' | sort > sorted_caps.txt
orange
apple
banana
EOF

sort < input.txt | uniq -c >> existing_sorted_uniq_counts.txt

cat << EOF | tr '[:lower:]' '[:upper:]' | sort >> existing_sorted_caps.txt
orange
apple
banana
EOF
