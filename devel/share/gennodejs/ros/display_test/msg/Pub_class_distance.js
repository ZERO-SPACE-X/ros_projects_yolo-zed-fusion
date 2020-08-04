// Auto-generated. Do not edit!

// (in-package display_test.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Pub_class_distance {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.classes = null;
      this.distance = null;
      this.x_center = null;
      this.y_center = null;
      this.id = null;
    }
    else {
      if (initObj.hasOwnProperty('classes')) {
        this.classes = initObj.classes
      }
      else {
        this.classes = [];
      }
      if (initObj.hasOwnProperty('distance')) {
        this.distance = initObj.distance
      }
      else {
        this.distance = [];
      }
      if (initObj.hasOwnProperty('x_center')) {
        this.x_center = initObj.x_center
      }
      else {
        this.x_center = [];
      }
      if (initObj.hasOwnProperty('y_center')) {
        this.y_center = initObj.y_center
      }
      else {
        this.y_center = [];
      }
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Pub_class_distance
    // Serialize message field [classes]
    bufferOffset = _arraySerializer.string(obj.classes, buffer, bufferOffset, null);
    // Serialize message field [distance]
    bufferOffset = _arraySerializer.float32(obj.distance, buffer, bufferOffset, null);
    // Serialize message field [x_center]
    bufferOffset = _arraySerializer.int64(obj.x_center, buffer, bufferOffset, null);
    // Serialize message field [y_center]
    bufferOffset = _arraySerializer.int64(obj.y_center, buffer, bufferOffset, null);
    // Serialize message field [id]
    bufferOffset = _arraySerializer.int16(obj.id, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Pub_class_distance
    let len;
    let data = new Pub_class_distance(null);
    // Deserialize message field [classes]
    data.classes = _arrayDeserializer.string(buffer, bufferOffset, null)
    // Deserialize message field [distance]
    data.distance = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [x_center]
    data.x_center = _arrayDeserializer.int64(buffer, bufferOffset, null)
    // Deserialize message field [y_center]
    data.y_center = _arrayDeserializer.int64(buffer, bufferOffset, null)
    // Deserialize message field [id]
    data.id = _arrayDeserializer.int16(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.classes.forEach((val) => {
      length += 4 + val.length;
    });
    length += 4 * object.distance.length;
    length += 8 * object.x_center.length;
    length += 8 * object.y_center.length;
    length += 2 * object.id.length;
    return length + 20;
  }

  static datatype() {
    // Returns string type for a message object
    return 'display_test/Pub_class_distance';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '26a7eb42f6a9f1a1625843bee8a7eb06';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string[] classes
    float32[] distance 
    int64[] x_center
    int64[] y_center
    int16[] id
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Pub_class_distance(null);
    if (msg.classes !== undefined) {
      resolved.classes = msg.classes;
    }
    else {
      resolved.classes = []
    }

    if (msg.distance !== undefined) {
      resolved.distance = msg.distance;
    }
    else {
      resolved.distance = []
    }

    if (msg.x_center !== undefined) {
      resolved.x_center = msg.x_center;
    }
    else {
      resolved.x_center = []
    }

    if (msg.y_center !== undefined) {
      resolved.y_center = msg.y_center;
    }
    else {
      resolved.y_center = []
    }

    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = []
    }

    return resolved;
    }
};

module.exports = Pub_class_distance;
