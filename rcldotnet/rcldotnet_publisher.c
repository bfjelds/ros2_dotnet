// Copyright 2016 Esteve Fernandez <esteve@apache.org>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <rmw/rmw.h>
#include <rcl/error_handling.h>
#include <rcl/rcl.h>
#include <rcl/node.h>
#include <rosidl_generator_c/message_type_support.h>

#include "rcldotnet_publisher.h"

void native_rcl_publish(void * publisher_handle, void * msg_struct, void * converter)
{
  typedef void * (* convert_from_dotnet_signature)(void *);
  convert_from_dotnet_signature convert_from_dotnet = (convert_from_dotnet_signature)converter;

  void * raw_ros_message = convert_from_dotnet(msg_struct);

  rcl_publisher_t * publisher = (rcl_publisher_t *)publisher_handle;

  rcl_ret_t ret = rcl_publish(publisher, raw_ros_message);

  // TODO(esteve): handle error
  if (ret != RCL_RET_OK) {
    assert(false);
  }
}