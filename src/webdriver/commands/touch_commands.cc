#include "commands/touch_commands.h"
#include "commands/response.h"
#include "webdriver_session.h"
#include "webdriver_util.h"
#include "webdriver_view_executor.h"

#include "base/values.h"
#include "base/bind.h"

namespace webdriver {


TouchCommand::TouchCommand(
    const std::vector<std::string>& path_segments,
    const DictionaryValue* const parameters)
    : ElementCommand(path_segments, parameters) {}

TouchCommand::~TouchCommand() {}

bool TouchCommand::DoesPost() const {
  return true;
}

TouchClickCommand::TouchClickCommand(const std::vector<std::string>& path_segments,
                           const DictionaryValue* const parameters)
    : TouchCommand(path_segments, parameters) {
}

TouchClickCommand::~TouchClickCommand() {}

void TouchClickCommand::ExecutePost(Response* const response) {
    Error* error = NULL;;
    std::string element_name;

    if (!GetStringParameter("element", &element_name))
    {
        response->SetError(new Error(
            kBadRequest, "Invalid command arguments"));
    }

    ElementId element = ElementId(element_name);


    session_->RunSessionTask(base::Bind(
            &ViewCmdExecutor::TouchClick,
            base::Unretained(executor_.get()),
            element,
            &error));

    if (error) {
        response->SetError(error);
        return;
    }
}

TouchDoubleClickCommand::TouchDoubleClickCommand(const std::vector<std::string>& path_segments,
                           const DictionaryValue* const parameters)
    : TouchCommand(path_segments, parameters) {
}

TouchDoubleClickCommand::~TouchDoubleClickCommand() {}


void TouchDoubleClickCommand::ExecutePost(Response *const response)
{
    Error* error = NULL;;
    std::string element_name;

    if (!GetStringParameter("element", &element_name))
    {
        response->SetError(new Error(
            kBadRequest, "Invalid command arguments"));
    }

    ElementId element = ElementId(element_name);

    session_->RunSessionTask(base::Bind(
            &ViewCmdExecutor::TouchDoubleClick,
            base::Unretained(executor_.get()),
            element,
            &error));

    if (error) {
        response->SetError(error);
        return;
    }
}

TouchDownCommand::TouchDownCommand(const std::vector<std::string>& path_segments,
                           const DictionaryValue* const parameters)
    : TouchCommand(path_segments, parameters) {
}

TouchDownCommand::~TouchDownCommand() {}

void TouchDownCommand::ExecutePost(Response *const response)
{
    Error* error = NULL;;
    int x, y;

    if (!GetIntegerParameter("x", &x) ||
        !GetIntegerParameter("y", &y)) {
      response->SetError(new Error(
          kBadRequest,
          "Missing or invalid 'x' or 'y' parameters"));
      return;
    }

    session_->RunSessionTask(base::Bind(
            &ViewCmdExecutor::TouchDown,
            base::Unretained(executor_.get()),
            x,
            y,
            &error));

    if (error) {
        response->SetError(error);
        return;
    }
}

TouchUpCommand::TouchUpCommand(const std::vector<std::string>& path_segments,
                           const DictionaryValue* const parameters)
    : TouchCommand(path_segments, parameters) {
}

TouchUpCommand::~TouchUpCommand() {}

void TouchUpCommand::ExecutePost(Response *const response)
{
    Error* error = NULL;;
    int x, y;

    if (!GetIntegerParameter("x", &x) ||
        !GetIntegerParameter("y", &y)) {
      response->SetError(new Error(
          kBadRequest,
          "Missing or invalid 'x' or 'y' parameters"));
      return;
    }

    session_->RunSessionTask(base::Bind(
            &ViewCmdExecutor::TouchUp,
            base::Unretained(executor_.get()),
            x,
            y,
            &error));

    if (error) {
        response->SetError(error);
        return;
    }
}

TouchMoveCommand::TouchMoveCommand(const std::vector<std::string>& path_segments,
                           const DictionaryValue* const parameters)
    : TouchCommand(path_segments, parameters) {
}

TouchMoveCommand::~TouchMoveCommand() {}

void TouchMoveCommand::ExecutePost(Response *const response)
{
    Error* error = NULL;;
    int x, y;

    if (!GetIntegerParameter("x", &x) ||
        !GetIntegerParameter("y", &y)) {
      response->SetError(new Error(
          kBadRequest,
          "Missing or invalid 'x' or 'y' parameters"));
      return;
    }

    session_->RunSessionTask(base::Bind(
            &ViewCmdExecutor::TouchMove,
            base::Unretained(executor_.get()),
            x,
            y,
            &error));

    if (error) {
        response->SetError(error);
        return;
    }
}

TouchScrollCommand::TouchScrollCommand(const std::vector<std::string>& path_segments,
                           const DictionaryValue* const parameters)
    : TouchCommand(path_segments, parameters) {
}

TouchScrollCommand::~TouchScrollCommand() {}

void TouchScrollCommand::ExecutePost(Response *const response)
{
    Error* error = NULL;;
    int x, y;

    if (!GetIntegerParameter("xoffset", &x) ||
        !GetIntegerParameter("yoffset", &y)) {
      response->SetError(new Error(
          kBadRequest,
          "Missing or invalid 'xoffset' or 'yoffset' parameters"));
      return;
    }

    std::string element_name;
    bool has_element_ = GetStringParameter("element", &element_name);

    if (has_element_) {
        ElementId element = ElementId(element_name);
        typedef void (ViewCmdExecutor::*TouchScroll)(const ElementId&, const int&, const int&, Error**);
        TouchScroll touchScroll = static_cast<TouchScroll>(&ViewCmdExecutor::TouchScroll);

        session_->RunSessionTask(base::Bind(
            touchScroll,
            base::Unretained(executor_.get()),
            element,
            x,
            y,
            &error));
    }
    else
    {
        typedef void (ViewCmdExecutor::*TouchScroll)(const int&, const int&, Error**);
        TouchScroll touchScroll = static_cast<TouchScroll>(&ViewCmdExecutor::TouchScroll);

        session_->RunSessionTask(base::Bind(
            touchScroll,
            base::Unretained(executor_.get()),
            x,
            y,
            &error));
    }

    if (error) {
        response->SetError(error);
        return;
    }

}

TouchLongClickCommand::TouchLongClickCommand(const std::vector<std::string>& path_segments,
                           const DictionaryValue* const parameters)
    : TouchCommand(path_segments, parameters) {
}

TouchLongClickCommand::~TouchLongClickCommand() {}

void TouchLongClickCommand::ExecutePost(Response *const response)
{
    Error* error = NULL;;
    Point location;
    std::string element_name;

    if (!GetStringParameter("element", &element_name))
    {
        response->SetError(new Error(
            kBadRequest, "Invalid command arguments"));
    }

    ElementId element = ElementId(element_name);

    session_->RunSessionTask(base::Bind(
            &ViewCmdExecutor::TouchLongClick,
            base::Unretained(executor_.get()),
            element,
            &error));

    if (error) {
        response->SetError(error);
        return;
    }

}

TouchFlickCommand::TouchFlickCommand(const std::vector<std::string>& path_segments,
                           const DictionaryValue* const parameters)
    : TouchCommand(path_segments, parameters) {
}

TouchFlickCommand::~TouchFlickCommand() {}

void TouchFlickCommand::ExecutePost(Response *const response)
{
    Error* error = NULL;;
    int xSpeed, ySpeed;
    int xoffset, yoffset, speed;
    std::string element_name;

    if (GetIntegerParameter("xspeed", &xSpeed) &&
        GetIntegerParameter("yspeed", &ySpeed))
    {
        typedef void (ViewCmdExecutor::*TouchFlick)(const int&, const int&, Error**);
        TouchFlick touchFlick = static_cast<TouchFlick>(&ViewCmdExecutor::TouchFlick);

        session_->RunSessionTask(base::Bind(
            touchFlick,
            base::Unretained(executor_.get()),
            xSpeed,
            ySpeed,
            &error));
    }
    else if (GetStringParameter("element", &element_name) && GetIntegerParameter("xoffset", &xoffset) &&
             GetIntegerParameter("yoffset", &yoffset) && GetIntegerParameter("speed", &speed))
    {
        ElementId element = ElementId(element_name);
        typedef void (ViewCmdExecutor::*TouchFlick)(const ElementId&, const int&, const int&, const int&, Error**);
        TouchFlick touchFlick = static_cast<TouchFlick>(&ViewCmdExecutor::TouchFlick);

        session_->RunSessionTask(base::Bind(
            touchFlick,
            base::Unretained(executor_.get()),
            element,
            xoffset,
            yoffset,
            speed,
            &error));
    }
    else
    {
        response->SetError(new Error(
            kBadRequest,
            "Missing or invalid parameters"));
        return;
    }

    if (error) {
        response->SetError(error);
        return;
    }

}


}

