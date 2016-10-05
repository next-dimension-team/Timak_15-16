/*
 * Message.h
 *
 *  Created on: 2.12.2013
 *      Author: Schade
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

class Message
{
	public:
		enum Enum
		{
			Set_Class_Diagram,
			Set_Activity_Diagram,
			Set_Sequence_Diagram,
			Set_Use_Case_Diagram,
			Popup_Insert,
			Popup_Modify,
			Popup_Delete
		};

		Message(int i);
		virtual ~Message();

		int getEnumValue();

	protected:
		int enumValue;
};

#endif /* MESSAGE_H_ */
