awk '/<BREAK>/ {p=1;next} p==1 {print}' "$1"_output.txt > "$1"_student
awk '{if (match($0,"<BREAK>")) exit; print}' "$1"_output.txt >"$1"_sol
diff "$1"_student "$1"_sol
