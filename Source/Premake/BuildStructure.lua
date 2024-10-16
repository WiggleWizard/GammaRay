BuildData = {}

function BuildData:new(o)
    o = o or {}   -- create object if user does not provide one
    setmetatable(o, self)
    self.__index = self
    
    self.project_public_includes = {}
    self.project_configure = {}
    self.project_declare = {}
    
    return o
end

build_data = BuildData:new();

function dep_assert_exists(project_name)
    if build_data.project_public_includes[project_name] == nil then
        error("Dependency ".. project_name .." does not exist")
        os.exit()
    end
end

function dep_configure(project_name, args)
    dep_assert_exists(project_name)
    build_data.project_configure[project_name](table.unpack(args))
end

function dep_decl(project_name)
    dep_assert_exists(project_name)
    build_data.project_declare[project_name]()
end

function dep_configure_and_decl(project_name, args)
    dep_configure(project_name, args)
    dep_decl(project_name)
end

function dep_inject_public_includes(project_name)
    dep_assert_exists(project_name)
    return table.unpack(build_data.project_public_includes[project_name]())
end


function dep_set_config_fn(project_name, fn)
    build_data.project_configure[project_name] = fn
end

function dep_set_public_includes_fn(project_name, fn)
    build_data.project_public_includes[project_name] = fn
end

function dep_declare_project_fn(project_name, fn)
    build_data.project_declare[project_name] = fn
end


current_dep = ""

function dependency(dep_name)
    current_dep = dep_name
end

function dep_config_fn(fn)
    dep_set_config_fn(current_dep, fn)
end