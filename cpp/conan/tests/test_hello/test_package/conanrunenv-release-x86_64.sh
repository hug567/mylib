echo "echo Restoring environment" > "/home/hx/code/mylib/cpp/conan/tests/test_hello/test_package/deactivate_conanrunenv-release-x86_64.sh"
for v in PATH
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "/home/hx/code/mylib/cpp/conan/tests/test_hello/test_package/deactivate_conanrunenv-release-x86_64.sh"
    else
        echo unset $v >> "/home/hx/code/mylib/cpp/conan/tests/test_hello/test_package/deactivate_conanrunenv-release-x86_64.sh"
    fi
done


export PATH="/home/hx/.conan2/p/helload3c181b34c27/p/bin:$PATH"