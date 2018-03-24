#pragma once

#include <vector>
#include <string>

#include "graphics/buffers/BufferLayout.hpp"

#include "utils/String.hpp"

namespace ht { namespace graphics {

	class ModelLayout : public BufferLayout {
	public:
		ModelLayout(const std::vector<std::string>& semanticNames, BufferLayout* layout)
			: BufferLayout(*layout) {
			HT_ASSERT(semanticNames.size() > m_Attributes.size(), "[ModelLayout] Too many semanticNames in the shader.");

			int semanticCount = 0;

			std::vector<BufferAttribute> modelAttributes; // The new attributes are going to get here

			for (const std::string& semanticName : semanticNames) {
				for (int i = 0; i < m_Attributes.size(); i++) {
					if (utils::String(semanticName) == m_Attributes[i].semanticName) {
						modelAttributes.push_back(m_Attributes[i]);
						semanticCount++;
						break;
					}
				}
			}
			m_Attributes = modelAttributes;
		}

		~ModelLayout();

	};

} }