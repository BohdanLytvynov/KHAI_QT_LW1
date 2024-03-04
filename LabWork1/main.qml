import QtQuick
import QtQuick.Controls
import LabTasks 1.0
import "scripts_main.js" as Js_main

Window {
    width: 840
    maximumWidth: 840
    maximumHeight: 480
    height: 480
    visible: true
    title: qsTr("Lab Work 1 Variant 17 Tasks 4 and 17")

    Task1BackEnd
    {
        id: task1_back

    }

    Task2BackEnd
    {
        id: task2_back
    }

    CButton
    {
        id: task1
        anchors.top: parent.top; anchors.topMargin: 20
        anchors.left: parent.left; anchors.leftMargin: 30
        content: qsTr("Task 1")

        onButtonClick:
        {
            task1_io.visible = true
            task2_io.visible = false
        }

    }

    CButton
    {
        id: task2
        anchors.top: parent.top; anchors.topMargin: 20
        anchors.left: task1.right; anchors.leftMargin: 20
        content: qsTr("Task 2")

        onButtonClick:
        {
            task1_io.visible = false
            task2_io.visible = true
        }
    }

    TaskIO
    {        
        id: task1_io
        anchors.top : task1.bottom; anchors.topMargin: 30
        anchors.left: parent.left; anchors.leftMargin: 10
        anchors.right: parent.right; anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        visible: true

        Text {
            id: task1_header
            text: qsTr("1) Task. Number 4 (17 according to list)")
            anchors.top: parent.top; anchors.topMargin: 10
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: task1_text_input
            text: qsTr("Please enter number: (1 - 366) then press \"Calculate\" ")
            anchors.top: task1_header.bottom; anchors.topMargin: 10
            anchors.left: parent.left; anchors.leftMargin: 10
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        TextField
        {
            id: date_input
            placeholderText: "Enter Date"
            anchors.top: task1_text_input.bottom; anchors.topMargin: 30
            anchors.left: parent.left; anchors.leftMargin: 10
            width: 400
            height: 50
            font.pointSize: 14
            font.italic: true
        }

        CButton
        {
            id: calc_button
            content: "Calculate"
            anchors.top: date_input.bottom; anchors.topMargin: 20;
            anchors.left: isLeapButton.right; anchors.leftMargin: 30
            width: 100
            onButtonClick: task1_back.calculate(date_input.text)
        }

        CButton
        {
            id: isLeapButton
            anchors.left: parent.left; anchors.leftMargin: 30;
            anchors.top: date_input.bottom; anchors.topMargin: 20;
            buttonToggleButton: false
            content: task1_back.leapYear? "Leap Year" : "Ordinary Year"
            onButtonClick:
            {
                if(!task1_back.leapYear)
                    task1_back.setleapYear(true)
                else
                    task1_back.setleapYear(false)
            }
        }

        Text {
            id: error_text
            text: qsTr("Here would be an error message")
            anchors.bottom: date_input.bottom;
            anchors.left: date_input.left; anchors.leftMargin: 20
            color: "red"
            font.pixelSize: 16
            visible: false
        }

        Text
        {
            id: result
            text:  qsTr("Calculation results: ")
            anchors.left: parent.left; anchors.leftMargin: 30
            anchors.top: isLeapButton.bottom; anchors.topMargin: 30
        }

        Connections
        {
            id:task1_back_connections
            target: task1_back

            function onErrorChanged()
            {
                error_text.visible = task1_back.isFail()

                error_text.text = task1_back.error                
            }

            function onMonthChanged()
            {
                error_text.visible = false

                result.text = qsTr("Calculation results: ")

                var r = "{ Day: " + task1_back.getDay() + " Month: " + task1_back.month.toString() + " }"

                result.text += r
            }
        }
    }

    TaskIO
    {       
        id: task2_io

        anchors.top : task1.bottom; anchors.topMargin: 30
        anchors.left: parent.left; anchors.leftMargin: 10
        anchors.right: parent.right; anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        visible: false

        Text {
            id: task2_header
            text: qsTr("2) Task. Number 17")
            anchors.top: parent.top; anchors.topMargin: 10
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: task2_text_input
            text: qsTr("Please choose the way how you would like to create array:")
            anchors.top: task2_header.bottom; anchors.topMargin: 10
            anchors.left: parent.left; anchors.leftMargin: 10
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        CButton
        {
            id: task2_type1
            buttonToggleButton: true
            content: qsTr("Manual fill")
            anchors.top: task2_text_input.bottom; anchors.topMargin: 20
            anchors.left: parent.left; anchors.leftMargin: 10

            onButtonClick:
            {                
                task2_back.setMode(1)

                if(task2_back.mode == 1)
                {
                    type1_rect.visible = true
                    type2_rect.visible = false
                    calculate.enabled = true
                }
            }
        }

        CButton
        {
            id: task2_type2
            buttonToggleButton: true
            content: qsTr("Random fill")
            anchors.top: task2_text_input.bottom; anchors.topMargin: 20
            anchors.left: task2_type1.right; anchors.leftMargin: 20

            onButtonClick:
            {                
                task2_back.setMode(2)

                if(task2_back.mode == 2)
                {
                    type1_rect.visible = false
                    type2_rect.visible = true

                    if(!task2_back.arrayGenerated())
                        calculate.enabled = false
                }
            }
        }

        Rectangle
        {
            id: type1_rect

            visible: true
            anchors.top: task2_type1.bottom; anchors.topMargin: 20
            anchors.left: parent.left; anchors.leftMargin: 10
            anchors.right: parent.right; anchors.rightMargin: 10
            border.color: "black"
            border.width: 2

            Text
            {
                id: type1_desc
                anchors.top: parent.top; anchors.topMargin: 30
                anchors.left: parent.left; anchors.leftMargin: 10
                text: qsTr("Please type here numbers and separate them with \",\". Example: (1,2,4,56,145):")
                font.bold: true                                
            }

            SmartTextField
            {
                id: arr_input
                anchors.top: type1_desc.bottom; anchors.topMargin: 20
                anchors.left: parent.left; anchors.leftMargin: 10
                anchors.right: parent.right; anchors.rightMargin: 10
                placeHolderText: qsTr("Enter numbers here")
                height: 40

                fontProperties.pixelSize: 14
                fontProperties.bold: true
                fontProperties.italic: true

                errorFontProperties.pixelSize: 16

                errorForeground: "red"

                errorText: task2_back.arrInputError               
            }
        }

        Rectangle
        {            
            id: type2_rect

            visible: false
            anchors.top: task2_type1.bottom; anchors.topMargin: 20
            anchors.left: parent.left; anchors.leftMargin: 10
            anchors.right: parent.right; anchors.rightMargin: 10
            border.color: "black"
            border.width: 2

            Text
            {
                id: type2_desc
                anchors.top: parent.top; anchors.topMargin: 30
                anchors.left: parent.left; anchors.leftMargin: 10
                text: qsTr("Set bounds and just press \"Generate\" and then \"Calculate\"! ")
                font.bold: true
            }

            SmartTextField
            {
                id: min
                width: 190
                height: 40
                anchors.top: type2_desc.bottom; anchors.topMargin: 20
                anchors.left: parent.left; anchors.leftMargin: 10

                fontProperties.pixelSize: 14
                fontProperties.bold: true
                fontProperties.italic: true

                errorForeground: "red"

                placeHolderText: qsTr("Minimum value")

                errorText: task2_back.minFieldError;

                onStfTextChanged:
                {
                    task2_back.setMin(min.text)

                    Js_main.checkGenEnabled(min, max, elem_count, generate);
                }
            }

            SmartTextField
            {
                id: max
                width: 190
                height: 40
                anchors.top: type2_desc.bottom; anchors.topMargin: 20
                anchors.left: min.right; anchors.leftMargin: 30

                fontProperties.pixelSize: 14
                fontProperties.bold: true
                fontProperties.italic: true

                errorForeground: "red"

                placeHolderText: qsTr("Maximum value")

                errorText: task2_back.maxFieldError;

                onStfTextChanged:
                {
                    task2_back.setMax(max.text)

                    Js_main.checkGenEnabled(min, max, elem_count, generate);
                }
            }

            SmartTextField
            {
                id: elem_count
                height: 40
                anchors.top: type2_desc.bottom; anchors.topMargin: 20
                anchors.left: max.right; anchors.leftMargin: 30
                anchors.right: parent.right; anchors.rightMargin: 10

                fontProperties.pixelSize: 14
                fontProperties.bold: true
                fontProperties.italic: true

                errorForeground: "red"

                placeHolderText: qsTr("Elements count")

                errorText: task2_back.elemCountFieldError;

                onStfTextChanged:
                {
                    task2_back.setElementCount(elem_count.text)

                    Js_main.checkGenEnabled(min, max, elem_count, generate);
                }
            }

            CButton
            {
                id: generate
                buttonToggleButton: true
                content: qsTr("Generate")
                anchors.left: parent.left; anchors.leftMargin: 20
                anchors.top: min.bottom; anchors.topMargin: 30

                onButtonClick:
                {
                    task2_back.generateArray();
                }

                onEnabledChanged:
                {
                    if(!generate.enabled)
                    {
                        generate.color = "grey";
                        generate.buttonToggleButton = false;
                    }
                    else
                    {
                        generate.color = "black";
                        generate.buttonToggleButton = true;
                    }
                }

                Component.onCompleted: generate.enabled = false;
            }

            Text {
                id: gen_result
                anchors.top: generate.bottom; anchors.topMargin: 20
                anchors.left: parent.left; anchors.leftMargin: 20
                text: qsTr("Generation result: ") + task2_back.genResult

                onTextChanged:
                {
                    if(task2_back.mode == 2 && !task2_back.failStatus())
                    {
                        calculate.enabled = true
                    }
                    else if(task2_back.mode == 2 && task2_back.failStatus())
                    {
                        calculate.enabled = false
                    }
                }
            }
        }

        CButton
        {
            id: calculate
            buttonToggleButton: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50

            anchors.left: parent.left; anchors.leftMargin: 50
            content: qsTr("Calculate")

            onButtonClick:
            {
                if(task2_back.mode == 1)
                    task2_back.setArray(arr_input.text)
                //else if(task2_back.mode == 2)

                task2_back.calculate()
            }

            onEnabledChanged:
            {
                if(!calculate.enabled)
                {
                    calculate.color = "grey";
                    calculate.buttonToggleButton = false;
                }
                else
                {
                    calculate.color = "black";
                    calculate.buttonToggleButton = true;
                }
            }

            Component.onCompleted:
            {
                if(task2_back.mode == 2)
                    calculate.enabled = false
                else
                    calculate.enabled = true
            }
        }

        Text {
            id: calc_result
            text: "The biggest 3 numbers: " + task2_back.calcResult

            anchors.left: parent.left; anchors.leftMargin: 10
            anchors.top: calculate.bottom; anchors.topMargin: 10;
            anchors.bottomMargin: 25
        }

    }
}

