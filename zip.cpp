/*
* Covariant Script Zip Bindings
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Copyright (C) 2017-2021 Michael Lee(李登淳)
*
* Email:   lee@covariant.cn, mikecovlee@163.com
* Github:  https://github.com/mikecovlee
* Website: http://covscript.org.cn
*/
#include <zip.hpp>

#include <covscript/dll.hpp>
#include <covscript/cni.hpp>

using cov_zip_t = std::shared_ptr<cov::zip>;

CNI_ROOT_NAMESPACE {
	CNI_V(extract, cov::zip_extract)
	CNI_NAMESPACE(openmode)
	{
		CNI_VALUE(read, cov::zip::openmode::read)
		CNI_VALUE(write, cov::zip::openmode::write)
		CNI_VALUE(append, cov::zip::openmode::append)
	}

	cov_zip_t open(const std::string& path, cov::zip::openmode mode)
	{
		return std::make_shared<cov::zip>(path, mode);
	}

	CNI(open)

	CNI_V(zip_extract, cov::zip_extract)

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

	CNI_NAMESPACE(zip_type)
	{
		CNI_V(is_open, [](const cov_zip_t &z) {
			return z->is_open();
		})
		cs::var get_entries(cov_zip_t& z) {
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
		CNI_V(read_entry_stream, [](cov_zip_t& z, const std::string& path, cs::ostream& os) {
			return z->read_entry_stream(path, *os);
		})
		CNI_V(write_entry_stream, [](cov_zip_t& z, const std::string& path, cs::istream& is) {
			return z->write_entry_stream(path, *is);
		})
		CNI_V(entry_add, [](cov_zip_t &z, const std::string& zip_path, const std::string& target_path) {
			return z->entry_add(zip_path, target_path);
		})
		CNI_V(entry_extract, [](cov_zip_t &z, const std::string& zip_path, const std::string& target_path) {
			return z->entry_extract(zip_path, target_path);
		})
		CNI_V(entry_delete, [](cov_zip_t &z, const std::string& path) {
			return z->entry_delete(path);
		})
	}
}

CNI_ENABLE_TYPE_EXT_V(entry_type, cov::zip::entry, cs::zip::entry)
CNI_ENABLE_TYPE_EXT_V(zip_type, cov_zip_t, cs::zip::zip_type)