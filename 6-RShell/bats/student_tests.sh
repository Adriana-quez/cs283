#!/usr/bin/env bats

# File: student_tests.sh
# 
# Create your unit tests suit in this file

setup() {
    ./dsh -s &
    sleep 2
}

@test "Example: check ls runs without errors" {
    run ./dsh <<EOF                
ls
EOF

    # Assertions
    [ "$status" -eq 0 ]
}

@test "Can exit client properly" {
    run ./dsh -c <<EOF
exit
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]' | tr -d '$\004')

    expected_output="socketclientmode:addr:127.0.0.1:1234dsh4>serverappearedtoterminate-exitingcmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    [ "$status" -eq 0 ]

}

@test "Client can handle single command" {
    run ./dsh -c <<EOF
echo hello
exit
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]' | tr -d '$\004')

    expected_output="socketclientmode:addr:127.0.0.1:1234dsh4>hellodsh4>serverappearedtoterminate-exitingcmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    [ "$status" -eq 0 ]
}

@test "Client can handle multiple commands" {
    run ./dsh -c <<EOF
echo hello
ls -al | wc -l
exit
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]' | tr -d '$\004')

    expected_output="socketclientmode:addr:127.0.0.1:1234dsh4>hellodsh4>16dsh4>serverappearedtoterminate-exitingcmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"


    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    [ "$status" -eq 0 ]
}

@test "Client changing directory with no commands changes nothing" {
    run ./dsh -c <<EOF
ls -al | wc -l
cd
ls -al | wc -l
exit
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]' | tr -d '$\004')

    expected_output="socketclientmode:addr:127.0.0.1:1234dsh4>16dsh4>dsh4>16dsh4>serverappearedtoterminate-exitingcmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"


    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    [ "$status" -eq 0 ]
}

@test "Client can change directory" {
    run ./dsh -c <<EOF
ls -al | wc -l
cd bats
ls -al | wc -l
exit
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]' | tr -d '$\004')

    expected_output="socketclientmode:addr:127.0.0.1:1234dsh4>16dsh4>dsh4>5dsh4>serverappearedtoterminate-exitingcmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"


    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    [ "$status" -eq 0 ]
}

@test "Client can stop server" {
    run ./dsh -c <<EOF
echo hello
stop-server
EOF

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]' | tr -d '$\004')

    expected_output="socketclientmode:addr:127.0.0.1:1234dsh4>hellodsh4>serverappearedtoterminate-exitingcmdloopreturned0"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    [ "$status" -eq 0 ]
}

@test "Client outputs error message if server is down" {
    run bash -c './dsh -c <<EOF
stop-server
EOF; &'
    run bash -c './dsh -c'

    # Strip all whitespace (spaces, tabs, newlines) from the output
    stripped_output=$(echo "$output" | tr -d '[:space:]' | tr -d '$\004')

    expected_output="connect:Connectionrefusedstartclient:Invalidargumentsocketclientmode:addr:127.0.0.1:1234cmdloopreturned-52"

    echo "Captured stdout:" 
    echo "Output: $output"
    echo "Exit Status: $status"
    echo "${stripped_output} -> ${expected_output}"

    # Check exact match
    [ "$stripped_output" = "$expected_output" ]

    [ "$status" -eq 0 ]
}