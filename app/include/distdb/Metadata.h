#ifndef METADATA_SERVER_H
#define METADATA_SERVER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "absl/log/log.h"

class Metadata {
public:
        uint32_t add( const std::string& key, const std::vector< uint32_t >& frames ) {
		auto it = keyToFramesMap_.find( key );
		if( it == keyToFramesMap_.end() ) {
			LOG(INFO) << "METADATA: Adding new key " << key;
			it = keyToFramesMap_.insert( { key , {} } ).first;
		}

		LOG(INFO) << "METADATA: Creating " << frames.size() << " new entries for " << key;
		it->second.insert( it->second.end(), frames.begin(), frames.end() );
		return 0;
	}

private:
	std::unordered_map< std::string, std::vector< uint32_t > > keyToFramesMap_;
};

# endif // INDEX_SERVER_H
