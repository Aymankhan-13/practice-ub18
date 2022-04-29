
def call(type){
  if type.equals('red'){
   sh "docker run  vtpl/ubuntu_build:18.04"
  }
  else {
    sh "docker run vtpl/ubuntu_build:20.04"
    }
  }
