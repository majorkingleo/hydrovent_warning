/*
 * ProgressInfo.cc
 *
 *  Created on: 28.01.2023
 *      Author: Martin Oberzalek <oberzalek@gmx.at>
 */

#ifndef SRC_PROGRESSINFO_CC_
#define SRC_PROGRESSINFO_CC_

#include "ProgressInfo.h"

void ProgressInfo::paintAll() {
	unsigned progress_to_paint = (progress * width) / 100.0;
	std::cout << "\nLoading " << name << " (Press CTRL+C to abort.)\n";

	// std::cout << "Progress to paint: " << progress_to_paint << std::endl;

	for( unsigned i = 0; i <= progress_to_paint; i++ ) {
		std::cout << "#";
	}

	std::cout << std::flush;

	last_progress_painted = progress_to_paint;
	repaint_complete_line = false;
}

void ProgressInfo::paintNext() {
	unsigned progress_to_paint = (progress * width) / 100.0;

	for( unsigned i = last_progress_painted; i < progress_to_paint; i++ ) {
		std::cout << "#" << std::flush;
	}

	last_progress_painted = progress_to_paint;
}


#endif /* SRC_PROGRESSINFO_CC_ */
