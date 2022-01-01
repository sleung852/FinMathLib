#pragma once

#include "stdafx.h"

class Chart {
    public:
        void setTitle( const std::string title ) {
            this->title = title;
        }

        std::string getTitle() const {
            return title;
        }

        void writeAsHTML( std::ostream& out ) const;
        void writeAsHTML( const std::string& file ) const;

    private:
        std::string title;
};