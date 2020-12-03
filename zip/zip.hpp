#pragma once
#include <string>
#include <vector>

#include "zip.h"

namespace cov {
	class zip {
		zip_t *m_zip = nullptr;

	public:
		struct entry {
			std::string name;
			bool is_dir = false;
			std::size_t size = 0;
			std::size_t crc32 = 0;
			entry(const std::string& n, bool is, std::size_t s, std::size_t c) :name(n), is_dir(is), size(s), crc32(c) {}
		};
		struct buffer {
            std::size_t size = 0;
			void *data = nullptr;
		private:
			friend class zip;
			buffer(std::size_t s) : size(s)
			{
				data = ::malloc(s);
			}
		public:
            buffer(buffer&& buff) noexcept {
                std::swap(size, buff.size);
                std::swap(data, buff.data);
            }
			~buffer()
			{
				::free(data);
			}
		};
		explicit zip(const std::string &path)
		{
			m_zip = zip_open(path.c_str(), 0, 'r');
		}
		~zip()
		{
			zip_close(m_zip);
		}
		std::vector<entry> get_entries()
		{
			std::vector<entry> entries;
			int n = zip_total_entries(m_zip);
			for (int i = 0; i < n; ++i) {
				zip_entry_openbyindex(m_zip, i);
				{
					const char *name = zip_entry_name(m_zip);
					int isdir = zip_entry_isdir(m_zip);
					unsigned long long size = zip_entry_size(m_zip);
					unsigned int crc32 = zip_entry_crc32(m_zip);
					entries.emplace_back(name, isdir, size, crc32);
				}
				zip_entry_close(m_zip);
			}
			return std::move(entries);
		}
		buffer entry_open(const std::string& path)
		{
			zip_entry_open(m_zip, path.c_str());
			buffer buff(zip_entry_size(m_zip));
			zip_entry_noallocread(m_zip, buff.data, buff.size);
			zip_entry_close(m_zip);
			return std::move(buff);
		}
	};

	void zip_extract(const std::string& zip_path, const std::string& target_path)
	{
		::zip_extract(zip_path.c_str(), target_path.c_str(), nullptr, nullptr);
	}
}