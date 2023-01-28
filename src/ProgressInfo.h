/*
 * ProgressInfo.h
 *
 *  Created on: 28.01.2023
 *      Author: martin
 */

#ifndef SRC_PROGRESSINFO_H_
#define SRC_PROGRESSINFO_H_

#include <iostream>
#include <string>

class ProgressInfo
{
	unsigned width;
	bool repaint_complete_line;
	unsigned progress;
	unsigned last_progress_painted;
	std::string name;

public:
	ProgressInfo( const std::string & name )
	: width(80),
	  repaint_complete_line(true),
	  progress(0),
	  last_progress_painted(0),
	  name( name )
	{}

	void setPercentageProgress( unsigned progress_ ) {
		progress = progress_;
	}

	void paint() {
		if( repaint_complete_line ) {
			paintAll();
		} else {
			paintNext();
		}
	}

	void setTainted( bool state = true ) {
		if( state ) {
			repaint_complete_line = true;
		}
	}

protected:

	void paintAll();
	void paintNext();
};



#endif /* SRC_PROGRESSINFO_H_ */
