pipeline {
    parameters {
        choice(name: 'PLATFORM_FILTER', choices: ['all', 'linux', 'windows'], description: 'Run on specific platform')
    }
    agent none
    stages {
        stage('BuildForDifferentOS') {
            matrix {
                axes {
                    axis {
                        name 'PLATFORM'
                        values 'ubuntu18', 'ubuntu20', 'windows'
                    }
                }
                stages {

                    stage('build_for_ubuntu18') {
                        when {
                            beforeAgent true
                            allOf {
                                expression { env.PLATFORM == 'ubuntu18' }
                                anyOf {
                                    expression { params.PLATFORM_FILTER == 'all' }
                                    expression { params.PLATFORM_FILTER == 'linux' }
                                }
                            }
                        }
                        agent {
                            docker {
                                image 'vtpl/ubuntu_build:18.04'
                                alwaysPull true
                                reuseNode true
                            }
                        }
                        stages {
                            stage('Build') {
                                environment {
                                    VCPKG_DEFAULT_BINARY_CACHE = '${WORKSPACE}/vcpkg_cache'
                                }
                                steps {
                                    sh "cat /etc/os-release"
                                    dir('vcpkg_cache') {
                                        writeFile file:'dummy', text:''
                                    }
                                    dir('thirdparty/vcpkg') {
                                        checkout([$class: 'GitSCM', branches: [[name: 'fb02a785618a1fbaced32b206171e09fd57d4622']], extensions: [], userRemoteConfigs: [[url: 'https://github.com/Microsoft/vcpkg.git']]])
                                    }
                                    cmakeBuild buildDir: 'build', buildType: 'Release', cleanBuild: false, cmakeArgs: '-DVCPKG_OVERLAY_TRIPLETS:STRING=${WORKSPACE} -DVCPKG_TARGET_TRIPLET:STRING=x64-mixed -DCMAKE_TOOLCHAIN_FILE:STRING=${WORKSPACE}/thirdparty/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_C_COMPILER_LAUNCHER:STRING=ccache -DCMAKE_CXX_COMPILER_LAUNCHER:STRING=ccache -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++', generator: 'Ninja', installation: 'InSearchPath', steps: [[withCmake: true]]
                                    archiveArtifacts artifacts: 'build/sample_cpp/sample_cpp', fingerprint: true, followSymlinks: false, onlyIfSuccessful: true
                                }
                            }
                        }
                    }
            }
        }
    }
}
}

