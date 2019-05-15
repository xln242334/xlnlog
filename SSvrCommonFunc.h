/*
*
*	一些简单的函数实现
*
*
*
*/

#ifndef _SSVRCOMMONFUNC_H_
#define _SSVRCOMMONFUNC_H_

#include <GeometryLib/GeometryLibIncludes.h>
#include <PowerSvrComponentDef.h>

class GVersionModel;
class GPSRPartInstance;
class GObject;
class GPort;
struct TPowerGridTileID;

class POWERSVRCOMPONENT_API SSvrCommonFunc
{
public :
	SSvrCommonFunc();
	~SSvrCommonFunc();

	/// 字符串匹配度算法，顺序匹配，str2是str1的子集才能匹配到0.5上，
	/// 字符串是有序匹配，str1、str2各读取一遍即可得到结果
	/// 支持通配符*表示任意0或多个字符
	/// 目前权重：
	/// 1、完全匹配的值是1；  例如： 123456、123456
	/// 2、头部匹配，其他地方不匹配，值是0.9-0.999；例如：123456、1234
	/// 3、尾部匹配，值是0.8-0.8999；例如：123456、3456
	/// 4、头、尾部不匹配，中间完全匹配，值：0.7-0.79999； 例如：123456、2345
	/// 5、分不同的段，局部匹配，值0.5-06999； 例如：123456、245
	/// 6、普通字符、通配符匹配后，str2长度仍然大于str1,值：0.1-0.49999；例如：1234、2345
	/// 7、其他，值：0.
	/// 特殊的：123456、123*、*123*、**123**、*、1*2*，这些字符串等价，匹配度是1.
	static double matchString(QString str1, QString str2, QChar chAnyChar = CGB('*'));

	/// 字符串比较
	/// 如果没有指定正则表达式，str1为原始字符串，返回str2是否匹配str1，str2可以使用*来当通配符。
	/// 否则，str1为原始字符串，检查正则表达式是否匹配str1。
	/// @param	&regExp	[in]	如果指定了正则表达式，使用正则表达式匹配
	/// @param	chAnyChar[in]	如果没有指定正则表达式，使用通配符来匹配，类似于oracle的‘%’匹配
	static bool compareStringEqual(QString str1, QString str2, QRegExp &regExp, QChar chAnyChar = CGB('%'));

	/// 判断A是否包含B
	static bool isStrAContainStrB(const QString &strA, const QString &strB);

	/// 0，0块在左上角
	/// 瓦片地图中块号和经纬度的转换， x表示经度（-180，180），y（-85,85）
	static int long2tilex(double lon, int nScale);
	static int lat2tiley(double lat, int nScale);
	static double tilex2long(int x, int nScale);
	static double tiley2lat(int y, int nScale);
	static bool getQueryRectByTileID(int x, int y, int nScale, GeRect2d &rect);
	static bool getWGS84RectByTileID(int x, int y, int nScale, GeRect2d &rect);

	static float  getGisRotation2MapboxRotation(float dGISRotation);

	/// 获取指定版本中受影响的分区
	static bool getVersionEffectPartList(int nVersionID, CDWordArray &arLoadedPart);

	/// 获取组织机构对应的所有分区和所有下级机构,包含本机构
	static void getChildPartAndOrgByOrg(int nOrgID, QSet<int> &setPartID, QSet<qint64> &setOrgID);
public:

};


#endif