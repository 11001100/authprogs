# copy input data for tests
add_test (NAME authprogs_system_test_copy_data
			COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)


set (NAME	"${PROJECT_NAME}_system_test")


# invalid argument
set (PASS_REGEX			"Invalid argument")

add_test				(NAME ${NAME}_-									COMMAND ${PROJECT_NAME} -)
set_tests_properties	(${NAME}_-										PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_--								COMMAND ${PROJECT_NAME} --)
set_tests_properties	(${NAME}_--										PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-a								COMMAND ${PROJECT_NAME} -a)
set_tests_properties	(${NAME}_-a										PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})
		
add_test				(NAME ${NAME}_-a_arg							COMMAND ${PROJECT_NAME} -a arg)
set_tests_properties	(${NAME}_-a_arg									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_--a								COMMAND ${PROJECT_NAME} --a)
set_tests_properties	(${NAME}_--a									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})
		
add_test				(NAME ${NAME}_--a_arg							COMMAND ${PROJECT_NAME} --a arg)
set_tests_properties	(${NAME}_--a_arg								PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})
		
add_test				(NAME ${NAME}_-aaa								COMMAND ${PROJECT_NAME} -aaa)
set_tests_properties	(${NAME}_-aaa									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})
		
add_test				(NAME ${NAME}_-aaa_arg							COMMAND ${PROJECT_NAME} -aaa arg)
set_tests_properties	(${NAME}_-aaa_arg								PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_--aaa								COMMAND ${PROJECT_NAME} --aaa)
set_tests_properties	(${NAME}_--aaa									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})
		
add_test				(NAME ${NAME}_--aaa_arg							COMMAND ${PROJECT_NAME} --aaa arg)
set_tests_properties	(${NAME}_--aaa_arg								PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})


# version
set (PASS_REGEX			"authprogs [0-9]+\\.[0-9]+\\.[0-9]+")

add_test				(NAME ${NAME}_-v								COMMAND ${PROJECT_NAME} -v)
set_tests_properties	(${NAME}_-v										PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-v_arg							COMMAND ${PROJECT_NAME} -v arg)
set_tests_properties	(${NAME}_-v_arg									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-v_-c								COMMAND ${PROJECT_NAME} -v -c)
set_tests_properties	(${NAME}_-v_-c									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})
		
add_test				(NAME ${NAME}_-v_-c_arg							COMMAND ${PROJECT_NAME} -v -c arg)
set_tests_properties	(${NAME}_-v_-c_arg								PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})
		
add_test				(NAME ${NAME}_-v_-l								COMMAND ${PROJECT_NAME} -v -l)
set_tests_properties	(${NAME}_-v_-l									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})
		
add_test				(NAME ${NAME}_-v_-l_arg							COMMAND ${PROJECT_NAME} -v -l arg)
set_tests_properties	(${NAME}_-v_-l_arg								PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})
		
add_test				(NAME ${NAME}_-v_-e								COMMAND ${PROJECT_NAME} -v -e)
set_tests_properties	(${NAME}_-v_-e									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-v_-e_5							COMMAND ${PROJECT_NAME} -v -e 5)
set_tests_properties	(${NAME}_-v_-e_5								PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-v_-h								COMMAND ${PROJECT_NAME} -v -h)
set_tests_properties	(${NAME}_-v_-h									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-c_arg_-v							COMMAND ${PROJECT_NAME} -c arg -v)
set_tests_properties	(${NAME}_-c_arg_-v								PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-l_arg_-v							COMMAND ${PROJECT_NAME} -l arg -v)
set_tests_properties	(${NAME}_-l_arg_-v								PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})


# help
set (PASS_REGEX			"Usage")

add_test				(NAME ${NAME}_-h								COMMAND ${PROJECT_NAME} -h)
set_tests_properties	(${NAME}_-h										PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-h_arg							COMMAND ${PROJECT_NAME} -h arg)
set_tests_properties	(${NAME}_-h_arg									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-h_-c								COMMAND ${PROJECT_NAME} -h -c)
set_tests_properties	(${NAME}_-h_-c									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-h_-c_arg							COMMAND ${PROJECT_NAME} -h -c arg)
set_tests_properties	(${NAME}_-h_-c_arg								PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-h_-l								COMMAND ${PROJECT_NAME} -h -l)
set_tests_properties	(${NAME}_-h_-l									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-h_-l_arg							COMMAND ${PROJECT_NAME} -h -l arg)
set_tests_properties	(${NAME}_-h_-l_arg								PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-h_-e								COMMAND ${PROJECT_NAME} -h -e)
set_tests_properties	(${NAME}_-h_-e									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-h_-e_5							COMMAND ${PROJECT_NAME} -h -e 5)
set_tests_properties	(${NAME}_-h_-e_5								PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-h_-v								COMMAND ${PROJECT_NAME} -h -v)
set_tests_properties	(${NAME}_-h_-v									PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-c_arg_-h							COMMAND ${PROJECT_NAME} -c arg -h)
set_tests_properties	(${NAME}_-c_arg_-h								PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})

add_test				(NAME ${NAME}_-l_arg_-h							COMMAND ${PROJECT_NAME} -l arg -h)
set_tests_properties	(${NAME}_-l_arg_-h								PROPERTIES PASS_REGULAR_EXPRESSION ${PASS_REGEX})


# configuration
add_test				(NAME ${NAME}_-c								COMMAND ${PROJECT_NAME} -c)
set_tests_properties	(${NAME}_-c										PROPERTIES PASS_REGULAR_EXPRESSION "requires an argument")

add_test				(NAME ${NAME}_-c_arg_-l_stdout					COMMAND ${PROJECT_NAME} -c arg -l stdout)
set_tests_properties	(${NAME}_-c_arg_-l_stdout						PROPERTIES PASS_REGULAR_EXPRESSION "Can not open configuration file")
set_property			(TEST ${NAME}_-c_arg_-l_stdout					PROPERTY ENVIRONMENT "SSH_CLIENT=192.168.100.100 64477 22" "SSH_ORIGINAL_COMMAND=echo WORKING!!!")


# log
add_test				(NAME ${NAME}_-l								COMMAND ${PROJECT_NAME} -l)
set_tests_properties	(${NAME}_-l										PROPERTIES PASS_REGULAR_EXPRESSION "requires an argument")

add_test				(NAME ${NAME}_-l_stdout_-c_arg					COMMAND ${PROJECT_NAME} -l stdout -c arg)
set_tests_properties	(${NAME}_-l_stdout_-c_arg						PROPERTIES PASS_REGULAR_EXPRESSION "Can not open configuration file")
set_property			(TEST ${NAME}_-l_stdout_-c_arg					PROPERTY ENVIRONMENT "SSH_CLIENT=192.168.100.100 64477 22" "SSH_ORIGINAL_COMMAND=echo WORKING!!!")


# log level
add_test				(NAME ${NAME}_-e								COMMAND ${PROJECT_NAME} -e)
set_tests_properties	(${NAME}_-e										PROPERTIES PASS_REGULAR_EXPRESSION "requires an argument")

add_test				(NAME ${NAME}_-e_arg							COMMAND ${PROJECT_NAME} -e arg)
set_tests_properties	(${NAME}_-e_arg									PROPERTIES PASS_REGULAR_EXPRESSION "Invalid log level")

add_test				(NAME ${NAME}_-e_6								COMMAND ${PROJECT_NAME} -e 6)
set_tests_properties	(${NAME}_-e_6									PROPERTIES PASS_REGULAR_EXPRESSION "Invalid log level")


# ip allowed
add_test				(NAME ${NAME}_allowed_-c_authprogs.conf_-l_stdout_ALL			COMMAND ${PROJECT_NAME} -c ${CMAKE_CURRENT_BINARY_DIR}/data/authprogs.conf -l stdout)
set_tests_properties	(${NAME}_allowed_-c_authprogs.conf_-l_stdout_ALL				PROPERTIES PASS_REGULAR_EXPRESSION "Successfully executed command")
set_property			(TEST ${NAME}_allowed_-c_authprogs.conf_-l_stdout_ALL			PROPERTY ENVIRONMENT "SSH_CLIENT=192.168.100.100 64477 22" "SSH_ORIGINAL_COMMAND=cvs up") 

add_test				(NAME ${NAME}_allowed_-c_authprogs.conf_-l_stdout_prefix_24		COMMAND ${PROJECT_NAME} -c ${CMAKE_CURRENT_BINARY_DIR}/data/authprogs.conf -l stdout)
set_tests_properties	(${NAME}_allowed_-c_authprogs.conf_-l_stdout_prefix_24			PROPERTIES PASS_REGULAR_EXPRESSION "Successfully executed command")
set_property			(TEST ${NAME}_allowed_-c_authprogs.conf_-l_stdout_prefix_24		PROPERTY ENVIRONMENT "SSH_CLIENT=192.168.100.100 64477 22" "SSH_ORIGINAL_COMMAND=echo WORKING!!!") 

add_test				(NAME ${NAME}_allowed_-c_authprogs.conf_-l_stdout_prefix_32		COMMAND ${PROJECT_NAME} -c ${CMAKE_CURRENT_BINARY_DIR}/data/authprogs.conf -l stdout)
set_tests_properties	(${NAME}_allowed_-c_authprogs.conf_-l_stdout_prefix_32			PROPERTIES PASS_REGULAR_EXPRESSION "Successfully executed command")
set_property			(TEST ${NAME}_allowed_-c_authprogs.conf_-l_stdout_prefix_32		PROPERTY ENVIRONMENT "SSH_CLIENT=10.2.1.100 64477 22" "SSH_ORIGINAL_COMMAND=ls")


# ip denied
add_test				(NAME ${NAME}_ip_denied_-c_authprogs.conf_-l_stdout				COMMAND ${PROJECT_NAME} -c ${CMAKE_CURRENT_BINARY_DIR}/data/authprogs.conf -l stdout)
set_tests_properties	(${NAME}_ip_denied_-c_authprogs.conf_-l_stdout					PROPERTIES PASS_REGULAR_EXPRESSION "Is not allowed to execute command")
set_property			(TEST ${NAME}_ip_denied_-c_authprogs.conf_-l_stdout				PROPERTY ENVIRONMENT "SSH_CLIENT=192.168.99.100 64477 22" "SSH_ORIGINAL_COMMAND=free") 


# command allowed
add_test				(NAME ${NAME}_command_allowed_-c_authprogs.conf_-l_stdout_star_match	COMMAND ${PROJECT_NAME} -c ${CMAKE_CURRENT_BINARY_DIR}/data/authprogs.conf -l stdout)
set_tests_properties	(${NAME}_command_allowed_-c_authprogs.conf_-l_stdout_star_match			PROPERTIES PASS_REGULAR_EXPRESSION "Successfully executed command")
set_property			(TEST ${NAME}_command_allowed_-c_authprogs.conf_-l_stdout_star_match	PROPERTY ENVIRONMENT "SSH_CLIENT=192.168.100.100 64477 22" "SSH_ORIGINAL_COMMAND=/usr/bin/mbuffer -q -s 128k -W 60 -m 1G|sudo zfs recv -F rpool/backup") 


# command denied
add_test				(NAME ${NAME}_command_denied_-c_authprogs.conf_-l_stdout_prefix_24		COMMAND ${PROJECT_NAME} -c ${CMAKE_CURRENT_BINARY_DIR}/data/authprogs.conf -l stdout)
set_tests_properties	(${NAME}_command_denied_-c_authprogs.conf_-l_stdout_prefix_24			PROPERTIES PASS_REGULAR_EXPRESSION "Is not allowed to execute command")
set_property			(TEST ${NAME}_command_denied_-c_authprogs.conf_-l_stdout_prefix_24		PROPERTY ENVIRONMENT "SSH_CLIENT=192.168.100.100 64477 22" "SSH_ORIGINAL_COMMAND=echo NOT WORKING!!!") 

add_test				(NAME ${NAME}_command_denied_-c_authprogs.conf_-l_stdout_star_match_1	COMMAND ${PROJECT_NAME} -c ${CMAKE_CURRENT_BINARY_DIR}/data/authprogs.conf -l stdout)
set_tests_properties	(${NAME}_command_denied_-c_authprogs.conf_-l_stdout_star_match_1		PROPERTIES PASS_REGULAR_EXPRESSION "Invalid characters in command.*, not allowed when using '\\*' matching")
set_property			(TEST ${NAME}_command_denied_-c_authprogs.conf_-l_stdout_star_match_1	PROPERTY ENVIRONMENT "SSH_CLIENT=192.168.100.100 64477 22" "SSH_ORIGINAL_COMMAND=/usr/bin/mbuffer -q -s 128k -W 60 -m 1G|sudo zfs recv -F rpool/backup|") 

add_test				(NAME ${NAME}_command_denied_-c_authprogs.conf_-l_stdout_star_match_2	COMMAND ${PROJECT_NAME} -c ${CMAKE_CURRENT_BINARY_DIR}/data/authprogs.conf -l stdout)
set_tests_properties	(${NAME}_command_denied_-c_authprogs.conf_-l_stdout_star_match_2		PROPERTIES PASS_REGULAR_EXPRESSION "Is not allowed to execute command")
set_property			(TEST ${NAME}_command_denied_-c_authprogs.conf_-l_stdout_star_match_2	PROPERTY ENVIRONMENT "SSH_CLIENT=192.168.100.100 64477 22" "SSH_ORIGINAL_COMMAND=/usr/bin/mbuffer -q -s 128k -W 60 -m 1G|sudo zfs recv -F|")

add_test				(NAME ${NAME}_command_denied_-c_authprogs.conf_-l_stdout_star_match_3	COMMAND ${PROJECT_NAME} -c ${CMAKE_CURRENT_BINARY_DIR}/data/authprogs.conf -l stdout)
set_tests_properties	(${NAME}_command_denied_-c_authprogs.conf_-l_stdout_star_match_3		PROPERTIES PASS_REGULAR_EXPRESSION "Invalid characters in command.*, not allowed when using '\\*' matching")
set_property			(TEST ${NAME}_command_denied_-c_authprogs.conf_-l_stdout_star_match_3	PROPERTY ENVIRONMENT "SSH_CLIENT=192.168.100.100 64477 22" "SSH_ORIGINAL_COMMAND=/usr/bin/mbuffer -q -s 128k -W 60 -m 1G|sudo zfs recv -F |") 