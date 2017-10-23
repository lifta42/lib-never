printf 'MetaTestcase: test testcase_start '

function test_output_and_exit_code {
  output=$1
  expected_output=$2
  exit_code=$3
  expected_exit_code=$4
  if [[ ${output} == ${expected_output} && \
    ${exit_code} == ${expected_exit_code} ]]
  then
    # do nothing here
    # copy this snippet and too lazy to modify
    return
  else
    printf ' FAILED\n'
    echo ">> execute \"${testcase_executable}\" manully and observe its behaviour"
    exit 1
  fi
}

printf '.'
read -r -d '' expected_output <<EOF
>> start testcase TestcaseStart
TestcaseStart: simple_test_1 . ok
TestcaseStart: simple_test_2 . ok
>> finish testcase TestcaseStart
>> start testcase MoreTestcase
MoreTestcase: a_red_test . ok
MoreTestcase: a_blue_test . FAILED
-> abort testcase: MoreTestcase
>> finish testcase MoreTestcase
>> start testcase MoreColor
MoreColor: a_yellow_test . FAILED
-> ignore failed test and continue
MoreColor: a_purple_test . ok
>> finish testcase MoreColor
EOF
testcase_executable=./testcase_start_test
output=$(${testcase_executable})
exit_code=$?

test_output_and_exit_code "$output" "$expected_output" $exit_code 1

printf '.'
read -r -d '' expected_output <<EOF
>> start testcase TestcaseStart
TestcaseStart: simple_test_1 . ok
TestcaseStart: simple_test_2 . ok
>> finish testcase TestcaseStart
EOF
testcase_executable=./testcase_start_test
output=$(${testcase_executable} TestcaseStart)
exit_code=$?

test_output_and_exit_code "$output" "$expected_output" $exit_code 0

printf '.'
read -r -d '' expected_output <<EOF
warning: not found testcase "NoExistTest"
>> start testcase MoreColor
MoreColor: a_yellow_test . FAILED
-> ignore failed test and continue
MoreColor: a_purple_test . ok
>> finish testcase MoreColor
EOF
testcase_executable=./testcase_start_test
output=$(${testcase_executable} NoExistTest MoreColor)
exit_code=$?

test_output_and_exit_code "$output" "$expected_output" $exit_code 1

printf ' ok\n'
