printf 'MetaTestcase: test testcase . '

read -r -d '' expected_output <<EOF
testcase name: test name .. FAILED
simple testcase: test 1 .. ok
simple testcase: test 2 .. FAILED
-> abort testcase: simple testcase
simple testcase: final flag . ok
ignore testcase: fail first . FAILED
-> ignore failed test and continue
ignore testcase: still test . ok
ignore testcase: final flag . ok
all right: test 1 . ok
all right: test 2 . ok
all right: final flag . ok
EOF

testcase_executable=./testcase_test
output=$(${testcase_executable})

if [[ ${output} == ${expected_output} ]]
then
  printf 'ok\n'
  exit 0
else
  printf 'FAILED\n'
  echo ">> execute \"${testcase_executable}\" manully and observe its behaviour"
  exit 1
fi
