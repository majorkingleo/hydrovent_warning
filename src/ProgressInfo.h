/*
 * ProgressInfo.h
 *
 *  Created on: 28.01.2023
 *      Author: Martin Oberzalek <oberzalek@gmx.at>
 */

#ifndef SRC_PROGRESSINFO_H_
#define SRC_PROGRESSINFO_H_

#include <iostream>
#include <string>

/*
 * ASCII Progressbar class
 *
 * Eg:
 *  Loading example.txt (Press CTRL+C to abort.)
 *  #########################################################################
 *  Warning: 00011 skipping invalid line: '5,5 -> 8,0'
 *
 *  Loading example.txt (Press CTRL+C to abort.)
 *  #################################################################################
 *
 * This class assumes that your terminal is 80 characters wide.
 * When paint() is called at the first time, the title line will be paintet
 *    "Loading example.txt (Press CTRL+C to abort.)"
 * and if there is already a progress, some # characters will be displayed.
 *
 * You can call paint() as often as you like. Only, when there is a progress,
 * (set via setPercentageProgress(x)) additional # characters will be displayed.
 *
 * if you destroyed the progressbar, by writing out some warnings or something,
 * call setTainted(). During the next paint() call the complete progressbar with title
 * will be regenerated.
 */
class ProgressInfo
{
	unsigned width;
	bool repaint_complete_line;
	unsigned progress;
	unsigned last_progress_painted;
	std::string name;

public:
	ProgressInfo( const std::string & name, unsigned width = 80 )
	: width(width),
	  repaint_complete_line(true),
	  progress(0),
	  last_progress_painted(0),
	  name( name )
	{}

	/*
	 * set progress to a value between 0 and 100
	 */
	void setPercentageProgress( unsigned progress_ ) {
		progress = progress_;
	}

	/*
	 * Paint the progress bar, complete or partial
	 */
	void paint() {
		if( repaint_complete_line ) {
			paintAll();
		} else {
			paintNext();
		}
	}

	/*
	 * set a mark, to redraw the complete progress bar
	 * next time paint() method is called.
	 */
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
