Gem::Specification.new do |s|
  s.name        = 'awe_native_extensions'
  s.version     = '0.0.0'
  s.date        = '2012-04-05'
  s.summary     = "awe_native_extensions"
  s.description = "The native extensions for awe"
  s.authors     = ["Sascha Lange", "Patrick Fox", "Julian Schmid"]
  s.email       = 'info@5dlab.com'
  s.files       = 	Dir.glob('lib/**/*.rb') +
  					Dir.glob('ext/**/*.{cpp,h,rb,i}')
  s.extensions = ['ext/aweext/extconf.rb']
  s.homepage    =
    'https://github.com/wackadoo/awe_native_extensions'
end