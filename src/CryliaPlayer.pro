# Enable auto-rebuild on source code changes
QMAKE_EXTRA_TARGETS += autorebuild
autorebuild.target = .build
autorebuild.depends = FORCE
autorebuild.commands = $$QMAKE_QMAKE ${QMAKE_FILE}
autorebuild.CONFIG += recursive
PRE_TARGETDEPS += .build
QMAKE_EXTRA_COMPILERS += autorebuild
autorebuild.input = FORCE
autorebuild.output = .build
autorebuild.commands += $$QMAKE_MAKE ${MAKEFILE}
QT += svg

