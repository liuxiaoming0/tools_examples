# 1、simple rule
def _printer_impl(ctx):
  # print("ctx={0}".format(dir(ctx)))
  print("Target Info, labels={}, attrs.number={}".format(ctx.label, ctx.attr.number))
  return DataInfo(number=ctx.attr.number)

printer = rule(
  implementation = _printer_impl,
  attrs = {
    "number" : attr.int(default = 0, doc="test", mandatory=True, values=[1,3,5])
  }
)

# 2、simple rule, use label、provider、file
DataInfo = provider()
def _printer_label_impl(ctx):
  # print(ctx.attr.mylabel)
  # print(type(ctx.attr.mylabel))
  # print(dir(ctx.attr.mylabel))
  # print(ctx.attr.mylabel[DataInfo])
  print(ctx.attr.mylabel[DataInfo].number)
  print(ctx.outputs.outfile)
  # ctx.actions.write(ctx.outputs.outfile, ctx.attr.msg, is_executable=False)
  ctx.actions.write(
    output=ctx.outputs.outfile, 
    content=ctx.attr.msg, 
    is_executable=False
  )
  return DefaultInfo(
    files = depset([ctx.outputs.outfile]),
  )

printer_with_label = rule(
  implementation = _printer_label_impl,
  attrs = {
    "msg" : attr.string(default="info1", doc="test", mandatory=False),
    "outfile": attr.output(mandatory=True),
    "mylabel": attr.label(),
  },
)

# 3、custom rule, use run
def _zip_cmd_impl(ctx):  
  # zip a.zip a.txt b.txt
  args  = ctx.actions.args()
  args.add(ctx.outputs.out)
  args.add_all(ctx.files.sources)

  ctx.actions.run(
    inputs = ctx.files.sources,
    outputs = [ctx.outputs.out],
    executable = "zip",
    arguments = [args],
  )

  return DefaultInfo(
    files = depset([ctx.outputs.out]),
  )

zip_cmd = rule(
  implementation = _zip_cmd_impl,
  attrs = {
    "sources": attr.label_list(allow_files = True),
    "out" : attr.output(mandatory=True),
  }
)