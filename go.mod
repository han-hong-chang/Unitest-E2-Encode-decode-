module gerrit.o-ran-sc.org/r/kpm

require (
	gerrit.o-ran-sc.org/r/ric-plt/xapp-frame v0.9.14
	github.com/spf13/viper v1.4.0
)

require golang.org/x/sys v0.0.0-20220728004956-3c1f35247d10 // indirect

replace gerrit.o-ran-sc.org/r/ric-plt/xapp-frame => gerrit.o-ran-sc.org/r/ric-plt/xapp-frame.git v0.9.14

replace gerrit.o-ran-sc.org/r/ric-plt/sdlgo => gerrit.o-ran-sc.org/r/ric-plt/sdlgo.git v0.7.0

replace gerrit.o-ran-sc.org/r/com/golog => gerrit.o-ran-sc.org/r/com/golog.git v0.0.2

go 1.18
