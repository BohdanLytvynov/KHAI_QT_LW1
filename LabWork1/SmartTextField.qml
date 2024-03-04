import QtQuick
import QtQuick.Controls
Rectangle {

    //Property

    property bool failed: false

    //Property alias

    //textField
    property alias text : text_field.text
    property alias placeHolderText: text_field.placeholderText
    property alias fontProperties : text_field.font
    property alias foreground : text_field.color
    property alias leftTextFieldOffset: text_field.anchors.leftMargin
    property alias topTextFieldOffset: text_field.anchors.topMargin
    property alias rightTextFieldOffset: text_field.anchors.rightMargin
    property alias bottomTextFieldOffset: text_field.anchors.bottomMargin

    //error text
    property alias errorText : error_text.text
    property alias errorForeground : error_text.color
    property alias errorFontProperties: error_text.font
    property alias errorTextOffset : error_text.anchors.leftMargin

    signal stfTextChanged()
    signal mouseEnter()
    signal mouseExit()


    id: root

    TextField
    {
        id: text_field
        anchors.top: parent.top;
        anchors.bottom: parent.bottom;
        anchors.left: parent.left
        anchors.right: parent.right

        onTextChanged:
        {
            parent.stfTextChanged()
        }
    }

    Text
    {
        id: error_text

        anchors.bottom: text_field.bottom;
        anchors.left: text_field.left;

        onTextChanged:
        {
            if(error_text.text.length > 0)
            {
                error_text.visible = true
                failed = true
            }
            else
            {
                error_text.visible = false
                failed = false
            }
        }
    }

}
