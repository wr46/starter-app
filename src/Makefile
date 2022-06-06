CC = g++
CFLAGS = -g -Wall -I/usr/local/include -L/usr/local/lib
TARGET = starter
HOME_PATH = $$( cd ~ && pwd )
APP_PATH = $(HOME_PATH)/.$(TARGET)
EXEC_PATH = $(APP_PATH)/executables
BIN_PATH = /usr/local/bin/$(TARGET)

$(TARGET): $(TARGET).cc
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cc -lyaml-cpp

install: $(TARGET)
	@[ ! -d $(EXEC_PATH) ] \
		&& mkdir -p -m 700 $(EXEC_PATH) \
		&& chmod 700 $(APP_PATH) || true
	@sudo cp ./executables/* $(EXEC_PATH) && chmod 500 $(EXEC_PATH)/*
	@[ -f ./config.yaml ] \
		|| sudo cp ./config.yaml.template ./config.yaml \
		&& sudo cp ./config.yaml $(APP_PATH)/config.yaml \
		&& chmod 400 $(APP_PATH)/config.yaml
	@echo "$(HOME_PATH)/.$(TARGET) folder created!"
	@sudo cp ./$(TARGET) $(BIN_PATH) \
		&& sudo chmod 755 $(BIN_PATH) \
		&& sudo chown root:root $(BIN_PATH)
	@echo "$(TARGET) application installed!"

run-exec:
ifndef flag
	$(error flag is not set)
endif
	@sudo $(TARGET) -e $(flag)

clean:
	$(RM) $(TARGET)
