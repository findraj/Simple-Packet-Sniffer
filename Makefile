all : clean publish

clean:
	dotnet clean
	# remove generated files
	rm -f ipk-sniffer
	rm -rf ./bin
	rm -rf ./obj
	rm -rf ./.idea
	rm -f xfindr01.zip

publish:
	dotnet publish -r osx-arm64 -p:PublishSingleFile=true -p:DebugType=None --self-contained true -o .

pack: clean
	zip -r xfindr01.zip .
