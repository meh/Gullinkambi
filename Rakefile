require 'rake'
require 'rake/clean'

CXX     = 'clang++'
CFLAGS  = "-Wall -Werror-implicit-function-declaration -std=c++11 -Iinclude -Isource #{ENV['CFLAGS']}"
LDFLAGS = "-lGL -lGLEW -lglut -lconfig++ #{ENV['LDFLAGS']}"

SOURCES = FileList['source/**/*.cpp']
OBJECTS = SOURCES.ext('o')

CLEAN.include(OBJECTS)
CLOBBER.include('Gullinkambi')

task :default => 'Gullinkambi'

file 'Gullinkambi' => OBJECTS do
	sh "#{CXX} -o Gullinkambi #{OBJECTS} #{LDFLAGS}"
end

rule '.o' => '.cpp' do |t|
	sh "#{CXX} #{CFLAGS} -o #{t.name} -c #{t.source}"
end
