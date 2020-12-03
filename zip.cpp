/*
* Covariant Script Zip Bindings
*
* Licensed under the Covariant General Public License,
* Version 1.1 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* https://covariant.cn/licenses/LICENSE-1.1
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Copyright (C) 2020 Michael Lee(李登淳)
* Email: mikecovlee@163.com
* Github: https://github.com/mikecovlee
*/
#include <zip.hpp>

#include <covscript/dll.hpp>
#include <covscript/cni.hpp>

using zip_type = std::shared_ptr<cov::zip>;

namespace cs_impl {
	template<>
	struct type_conversion_cs<cov::zip&> {
		using source_type=zip_type;
	};

	template<>
	struct type_conversion_cs<const cov::zip&> {
		using source_type=zip_type;
	};

	template<>
	struct type_convertor<zip_type, cov::zip&> {
		static cov::zip& convert(const zip_type &s)
		{
			return *s;
		}
	};

	template<>
	struct type_convertor<zip_type, const cov::zip&> {
		static const cov::zip& convert(const zip_type &s)
		{
			return *s;
		}
	};
}

CNI_ROOT_NAMESPACE {
	CNI_V(extract, cov::zip_extract)
	CNI_NAMESPACE(openmode)
	{
		CNI_VALUE(read, cov::zip::openmode::read)
		CNI_VALUE(write, cov::zip::openmode::write)
		CNI_VALUE(append, cov::zip::openmode::append)
	}

	zip_type open(const std::string& path, cov::zip::openmode mode)
	{
		return std::make_shared<cov::zip>(path, mode);
	}
	CNI(open)

	CNI_NAMESPACE(entry_type)
	{
		CNI_VISITOR_V(name, [](const cov::zip::entry& e) {
			return e.name;
		})
		CNI_VISITOR_V(is_dir, [](const cov::zip::entry& e) {
			return e.is_dir;
		})
		CNI_VISITOR_V(size, [](const cov::zip::entry& e) {
			return e.size;
		})
		CNI_VISITOR_V(crc32, [](const cov::zip::entry& e) {
			return std::to_string(e.crc32);
		})
	}

	CNI_NAMESPACE(zip_typeype)
	{
		CNI_V(is_open, &cov::zip::is_open)
		cs::var get_entries(zip_type& z) {
			auto opt = z->get_entries();
			if (!opt)
				return cs::null_pointer;
			cs::var value = cs::var::make<cs::array>();
			cs::array &arr = value.val<cs::array>();
			for (auto &it:*opt)
				arr.emplace_back(it);
			return value;
		}
		CNI(get_entries)
		CNI_V(read_entry_stream, [](zip_type& z, const std::string& path, cs::ostream& os) {
			return z->read_entry_stream(path, *os);
		})
		CNI_V(write_entry_stream, [](zip_type& z, const std::string& path, cs::istream& is) {
			return z->write_entry_stream(path, *is);
		})
		CNI_V(entry_add, &cov::zip::entry_add)
		CNI_V(entry_extract, &cov::zip::entry_extract)
		CNI_V(entry_delete, &cov::zip::entry_delete)
	}
}

CNI_ENABLE_TYPE_EXT_V(entry_type, cov::zip::entry, cs::zip::entry)
CNI_ENABLE_TYPE_EXT_V(zip_typeype, zip_type, cs::zip::zip_type)