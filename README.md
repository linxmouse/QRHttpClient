# Qt HTTP Client Demo

A modern, lightweight HTTP client library for Qt applications with JSON serialization support. This library provides a simple way to make HTTP requests and handle JSON responses with automatic serialization/deserialization.

## Features

- Support for common HTTP methods (GET, POST, PUT, DELETE)
- Automatic JSON serialization/deserialization
- Type-safe JSON property handling
- Support for query string parameters
- Custom logger implementation
- Comprehensive error handling
- Template-based serialization for STL and Qt containers

## Dependencies

- Qt 5.x (Core and Network modules)
- C++11 or later
- CMake 3.10 or later

## Building the Project

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Basic HTTP Request

```cpp
// Make a simple GET request
QString url = "http://api.example.com/data";
IResult result = httpClient->Get(url);

if (result.code() == 0) {
    // Handle successful response
    qDebug() << result.data();
} else {
    qCritical() << result.message();
}
```

### Working with Query Parameters

```cpp
// Using QJsonObject for query parameters
QString baseUrl = "http://api.example.com/endpoint";
QJsonObject params{{"param1", "value1"}, {"param2", "value2"}};
QUrl url = httpClient->createWithQuerystring(baseUrl, params);

// Using QMap for query parameters
QMap<QString, QString> queryParams;
queryParams["param1"] = "value1";
queryParams["param2"] = "value2";
QUrl url = httpClient->createWithQuerystring(baseUrl, queryParams);
```

### JSON Serialization

Define your data model:

```cpp
class MyModel : public JsonSerializable
{
    Q_GADGET
    JSON_SERIALIZABLE
public:
    JSON_PROPERTY(QString, name)
    JSON_PROPERTY(int, age)
    JSON_PROPERTY(QList<QString>, tags)
};
```

Use the model:

```cpp
MyModel model;
model.set_name("John");
model.set_age(30);

// Serialize to JSON
QJsonObject json = model.toJson();
QByteArray rawJson = model.toRawJson();

// Deserialize from JSON
MyModel newModel;
newModel.fromJson(jsonData);
```

## Logger Configuration

The project includes a custom logger (TyLogger) that:

- Writes logs to daily rotating files
- Supports different log levels (DEBUG, INFO, WARN, ERROR, FATAL)
- Includes timestamps and source file information in debug builds
- Thread-safe implementation
- Asynchronous file writing

To use the logger:

```cpp
// Install the custom message handler
qInstallMessageHandler(TyLogger::customMessageHandler);

// Use Qt's logging macros
qDebug() << "Debug message";
qInfo() << "Info message";
qWarning() << "Warning message";
qCritical() << "Critical error";
```

## Design Patterns

The library implements several design patterns:

- Singleton pattern for HTTP client and logger
- Template method pattern for serialization
- CRTP (Curiously Recurring Template Pattern) for JSON serialization
- Observer pattern for network replies

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Thanks to Qt framework for providing excellent networking capabilities
- Inspired by modern C++ design patterns and best practices